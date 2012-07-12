#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"
#include "godunion.h"
#include "storage.h"
#include "goderror.h"
#include "asserts.h"

namespace asn1
{
#include "God.h"
}
#include "godasn1.h"

namespace libgod
{

	class StorageImpl : boost::noncopyable
	{
	public:
		GodASN1 asn1Storage;

		void convertToASN1Data (const Union& aunion, asn1::God& root);
		void convertFromASN1Data (Union& aunion, const asn1::God& root);
	};

	// does not work with pointers
	template <class T>
	void zeroed(T& t, 
					typename boost::disable_if<boost::is_pointer<T> >::type* dummy = 0)
	{
		memset(&t, 0, sizeof(T));
	}

	template <class T>
	T* newzeroed()
	{
		T* ptr = new T;
		zeroed(*ptr);
		return ptr;
	}

	void StorageImpl::convertToASN1Data (const Union& aunion, asn1::God& root)
	{
		const int formatVersion = 1;
		const std::string errReason = "Converting to ASN1 failed";
		asn1::Set *dataSet;
		asn1::Point *dataPoint;
		asn1::REAL_t *dataReal;

		zeroed(root);
		
		// god.header
		if (asn1::asn_long2INTEGER(&root.header.version, formatVersion))
			throw GodError(errReason, errno);
		
		// it's an utf8 string
		if (OCTET_STRING_fromString(&root.header.comment, ""))
			throw GodError(errReason, errno);

		// god.metric
		if (asn1::asn_long2INTEGER(&root.metric.parameterDim, aunion.dimParameter()))
			throw GodError(errReason, errno);
		if (asn1::asn_long2INTEGER(&root.metric.criteriaDim, aunion.dimCriteria()))
			throw GodError(errReason, errno);
		if (asn1::asn_long2INTEGER(&root.metric.setsCount, aunion.size()))
			throw GodError(errReason, errno);

		// god.union
		for (Union::const_iterator itSet = aunion.begin(); 
					itSet != aunion.end(); ++itSet)
		{
			// god.union.set
			dataSet = newzeroed<asn1::Set>();
			if (asn1::asn_long2INTEGER(&dataSet->pointCount, itSet->size()))
				throw GodError(errReason, errno);

			for (Set::const_iterator itPoint = itSet->begin(); 
					itPoint != itSet->end(); ++itPoint)
			{
				dataPoint = newzeroed<asn1::Point>();
				// god.union.set.point.parameters
				for (size_t ind = 0; ind < itPoint->dimParameter(); ++ind)
				{
					dataReal = newzeroed<asn1::REAL_t>();
					if (asn1::asn_double2REAL(dataReal, itPoint->parameterAt(ind)))
						throw GodError(errReason, errno);
					if (ASN_SEQUENCE_ADD(&dataPoint->parameters, dataReal))
						throw GodError(errReason, errno);
				}
				// god.union.set.point.criteria
				for (size_t ind = 0; ind < itPoint->dimCriteria(); ++ind)
				{
					dataReal = newzeroed<asn1::REAL_t>();
					if (asn1::asn_double2REAL(dataReal, itPoint->criterionAt(ind)))
						throw GodError(errReason, errno);
					if (ASN_SEQUENCE_ADD(&dataPoint->criteria, dataReal))
						throw GodError(errReason, errno);
				}
				// push the point to the set
				if (ASN_SEQUENCE_ADD(&dataSet->points, dataPoint))
					throw GodError(errReason, errno);
			}
			if (ASN_SEQUENCE_ADD(&root.Union, dataSet))
				throw GodError(errReason, errno);
		}

		ASSERT_EQUAL(root.Union.list.count,aunion.size());
	}

	int stringFromOctetString (const asn1::UTF8String_t *s, std::string& result)
	{
		if (s->buf)
			result.assign(s->buf, s->buf + s->size);
		else
			result.clear();
		return 0;
	}

	void StorageImpl::convertFromASN1Data (Union& aunion, const asn1::God& root)
	{
		const int formatVersion = 1;
		const std::string errReason = "Converting from ASN1 failed";

		long actualVersion;
		std::string comment;
		long dimParameter, dimCriteria, setsCount, pointCount;
		double value;

		asn1::Set *dataSet;
		asn1::Point *dataPoint;
		asn1::REAL_t *dataReal;

		// god.header
		if (asn1::asn_INTEGER2long(&root.header.version, &actualVersion))
			throw GodError(errReason, errno);
		if (actualVersion > formatVersion)
			throw GodError("Cannot read this newer format");
		
		// it's an utf8 string
		if (stringFromOctetString(&root.header.comment, comment))
			throw GodError(errReason, errno);

		// god.metric
		if (asn1::asn_INTEGER2long(&root.metric.parameterDim, &dimParameter))
			throw GodError(errReason, errno);
		if (asn1::asn_INTEGER2long(&root.metric.criteriaDim, &dimCriteria))
			throw GodError(errReason, errno);
		if (asn1::asn_INTEGER2long(&root.metric.setsCount, &setsCount))
			throw GodError(errReason, errno);

		// create non-bare union with right dimensions
		aunion = libgod::Union(dimParameter, dimCriteria);
		
		ASSERT_EQUAL(root.Union.list.count, setsCount);

		for (size_t setIndex = 0; setIndex < setsCount; ++setIndex)
		{
			libgod::Set& aset = aunion.add();

			dataSet = root.Union.list.array[setIndex];
			if (asn1::asn_INTEGER2long(&dataSet->pointCount, &pointCount))
				throw GodError(errReason, errno);

			ASSERT_EQUAL(dataSet->points.list.count, pointCount);

			for (size_t pointIndex = 0; pointIndex < pointCount; ++pointIndex)
			{
				libgod::Point& apoint = aset.add();

				dataPoint = dataSet->points.list.array[pointIndex];
			
				ASSERT_EQUAL(dataPoint->parameters.list.count, dimParameter);
				ASSERT_EQUAL(dataPoint->criteria.list.count, dimCriteria);

				for (size_t ind = 0; ind < dimParameter; ++ind)
				{
					if (asn1::asn_REAL2double(dataPoint->parameters.list.array[ind], &value))
						throw GodError(errReason, errno);
					apoint.setParameterAt(ind, value);
				}
				for (size_t ind = 0; ind < dimCriteria; ++ind)
				{
					if (asn1::asn_REAL2double(dataPoint->criteria.list.array[ind], &value))
						throw GodError(errReason, errno);
					apoint.setCriterionAt(ind, value);
				}
			}
		}
	}



	Storage::Storage (const std::string& file)
		:	m_impl(new StorageImpl),
			m_file(file)
	{
	}

	Storage::~Storage()
	{
	}

	void Storage::write (const Union& aunion)
	{
		m_impl->convertToASN1Data(aunion, *(m_impl->asn1Storage.getRoot()));
		m_impl->asn1Storage.writeToFile(m_file);
	}

	void Storage::read (Union& aunion)
	{
		m_impl->asn1Storage.readFromFile(m_file);
		m_impl->convertFromASN1Data(aunion, *(m_impl->asn1Storage.getRoot()));
	}
	
	void Storage::dump (std::ostream& os, const Union& aunion)
	{
		m_impl->convertToASN1Data(aunion, *(m_impl->asn1Storage.getRoot()));
		os << m_impl->asn1Storage;
	}
};
