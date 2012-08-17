#ifndef LIBGOD_INC__CONTAINER_H
#define LIBGOD_INC__CONTAINER_H

namespace libgod
{

	namespace details
	{
		template <class T, class Comp>
		void genericSort (typename std::vector<T>& cont, const Comp& comp)
		{
			std::sort(cont.begin(), cont.end(), comp);
		}
		
		template <class T, class Comp>
		void genericSort (typename std::list<T>& cont, const Comp& comp)
		{
			cont.sort(comp);
		}
	};

	template <typename T, typename Inner>
	class Container
	{
	protected:
		typedef Container<T, Inner> SelfType;

		bool m_isBare;

		size_t m_dimParameter;
		size_t m_dimCriteria;

		Inner m_items;

		const std::string m_classDesc;
		
		Metadata m_metadata;


		Container (const std::string& classDesc, size_t dimParameter, size_t dimCriteria)
			: m_isBare(false),
				m_dimParameter(dimParameter),
				m_dimCriteria(dimCriteria),
				m_classDesc(classDesc)
			{
				if (dimParameter <= 0 || dimCriteria <= 0)
					throw GodError("dimensions should be posititive");
			}
		
		Container (const SelfType& rhs)
			: m_isBare(false),
			 	m_dimParameter(rhs.m_dimParameter),
				m_dimCriteria(rhs.m_dimCriteria),
				m_items(rhs.m_items),
				m_classDesc(rhs.m_classDesc),
				m_metadata(rhs.m_metadata)
			{
				if (m_dimParameter <= 0 || m_dimCriteria <= 0)
					throw GodError("dimensions should be posititive");
			}

		explicit Container (const std::string& classDesc)
			: m_isBare(true),
			 	m_dimParameter(1),
				m_dimCriteria(1),
				m_classDesc(classDesc)
			{
			}

		Container ()
			: m_isBare(true),
			 	m_dimParameter(1),
				m_dimCriteria(1),
				m_classDesc("")
			{
			}

		~Container()
		{
		}

		bool deepEquals (const SelfType& rhs) const
		{
			return
				m_dimParameter == rhs.m_dimParameter &&
				m_dimCriteria == rhs.m_dimCriteria &&
				m_items == rhs.m_items;
		}

		void preConditionBare() const
		{
			if (m_isBare)
				throw GodError("Trying to get data from bare " + m_classDesc);
		}

	public:
		
		typedef typename Inner::iterator iterator;
		typedef typename Inner::const_iterator const_iterator;
	
		SelfType& operator= (const SelfType& rhs)
		{
			if (this != &rhs)
			{
				if (m_isBare)
				{
					m_dimParameter = rhs.m_dimParameter;
					m_dimCriteria = rhs.m_dimCriteria;
					m_metadata = rhs.m_metadata;
				}
				else
				{
					if (m_dimParameter != rhs.m_dimParameter || m_dimCriteria != rhs.m_dimCriteria)
					{
						throw GodError("cannot assign item with a different metric");
					}
				}
				m_items = rhs.m_items;
				m_metadata = rhs.m_metadata;
				m_isBare = false;
			}
			return *this;
		}

		// XXX: comparison doesn't care about metadata. is it okay?
		bool operator== (const SelfType& rhs) const
		{
			return fullyEquals(rhs);
		}

		bool operator!= (const SelfType& rhs) const
		{
			return !fullyEquals(rhs);
		}

		size_t dimParameter() const
		{
			return m_dimParameter;
		}

		size_t dimCriteria() const
		{
			return m_dimCriteria;
		}

		size_t size() const
		{
			return m_items.size();
		}

		bool empty() const
		{
			return m_items.empty();
		}

		void clear()
		{
			preConditionBare();
			m_items.clear();
		}

		bool isBare() const
		{
			return m_isBare;
		}

		Metadata& metadata()
		{
			return m_metadata;
		}
		
		const Metadata& metadata() const
		{
			return m_metadata;
		}


		iterator begin()
		{
			preConditionBare();
			return m_items.begin();
		}

		const_iterator begin() const
		{
			preConditionBare();
			return m_items.begin();
		}

		iterator end()
		{
			preConditionBare();
			return m_items.end();
		}

		const_iterator end() const
		{
			preConditionBare();
			return m_items.end();
		}

		iterator atIndex(size_t ind)
		{
			preConditionBare();
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		const_iterator atIndex(size_t ind) const
		{
			preConditionBare();
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			const_iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		T& add()
		{
			preConditionBare();
			m_items.push_back(T(m_dimParameter, m_dimCriteria));
			return m_items.back();
		}

		void add(const T& item)
		{
			if (isBare())
			{
				if (item.isBare())
					preConditionBare();
				m_dimParameter = item.dimParameter();
				m_dimCriteria = item.dimCriteria();
				m_isBare = false;
			}
			else
			{
				preConditionBare();
				if (item.dimParameter() != m_dimParameter ||
						item.dimCriteria() != m_dimCriteria)
					throw GodError("added item has a different dimension than a set");
			}
			m_items.push_back(item);
		}

		void remove(size_t ind)
		{
			preConditionBare();
			remove(atIndex(ind));
		}

		void remove(iterator iter)
		{
			preConditionBare();
			if (iter >= end())
				throw GodOutOfRangeError(m_classDesc + " item ", std::distance(begin(), iter), size());
			m_items.erase(iter);
		}

		template <class Comp>
		void sort(const Comp& comp)
		{
			preConditionBare();
			details::genericSort(m_items, comp);
		}

		const T& operator[] (size_t ind) const
		{
			return *atIndex(ind);
		}

		T& operator[] (size_t ind)
		{
			return *atIndex(ind);
		}

		void swapItems (size_t left_ind, size_t right_ind)
		{
			preConditionBare();
			if (left_ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", left_ind, size());
			if (right_ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", right_ind, size());
			std::swap((*this)[left_ind], (*this)[right_ind]);
		}
	};



};

#endif

