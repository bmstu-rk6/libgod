#ifndef LIBGOD_INC__CONTAINER_H
#define LIBGOD_INC__CONTAINER_H

namespace libgod
{

	template <typename T, typename Inner>
	class Container
	{
	protected:
		typedef Container<T, Inner> SelfType;

		const size_t m_dimParameter;
		const size_t m_dimCriteria;

		Inner m_items;

		const std::string m_classDesc;

		Container (const std::string& classDesc, size_t dimParameter, size_t dimCriteria)
			: m_dimParameter(dimParameter),
				m_dimCriteria(dimCriteria),
				m_classDesc(classDesc)
			{
				if (dimParameter <= 0 || dimCriteria <= 0)
					throw GodError("dimensions should be posititive");
			}
		
		Container (const SelfType& rhs)
			: m_dimParameter(rhs.m_dimParameter),
				m_dimCriteria(rhs.m_dimCriteria),
				m_classDesc(rhs.m_classDesc)
			{
				if (m_dimParameter <= 0 || m_dimCriteria <= 0)
					throw GodError("dimensions should be posititive");
			}

		Container ()
			: m_dimParameter(1),
				m_dimCriteria(1),
				m_classDesc("")
			{
			}

	public:
		
		typedef typename Inner::iterator iterator;
		typedef typename Inner::const_iterator const_iterator;
	
		SelfType& operator= (const SelfType& rhs)
		{
			if (this != &rhs)
			{
				if (m_dimParameter != rhs.m_dimParameter || 
						m_dimCriteria != rhs.m_dimCriteria)
				{
					throw GodError("cannot assign item with a different metric");
				}
				m_items = rhs.m_items;
			}
			return *this;
		}

		bool operator== (const SelfType& rhs) const
		{
			return
				m_dimParameter == rhs.m_dimParameter &&
				m_dimCriteria == rhs.m_dimCriteria &&
				m_items == rhs.m_items;
		}

		bool operator!= (const SelfType& rhs) const
		{
			return !(*this == rhs);
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

		void clear()
		{
			m_items.clear();
		}


		iterator begin()
		{
			return m_items.begin();
		}

		const_iterator begin() const
		{
			return m_items.begin();
		}

		iterator end()
		{
			return m_items.end();
		}

		const_iterator end() const
		{
			return m_items.end();
		}

		iterator atIndex(size_t ind)
		{
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		const_iterator atIndex(size_t ind) const
		{
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			const_iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		T& add()
		{
			m_items.push_back(T(m_dimParameter, m_dimCriteria));
			return m_items.back();
		}

		void add(const T& item)
		{
			if (item.dimParameter() != m_dimParameter ||
					item.dimCriteria() != m_dimCriteria)
				throw GodError("added item has a different dimension than a set");
			m_items.push_back(item);
		}

		void remove(size_t ind)
		{
			remove(atIndex(ind));
		}

		void remove(iterator iter)
		{
			if (iter >= end())
				throw GodOutOfRangeError(m_classDesc + " item ", std::distance(begin(), iter), size());
			m_items.erase(iter);
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
			if (left_ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", left_ind, size());
			if (right_ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", right_ind, size());
			std::swap(m_items[left_ind], m_items[right_ind]);
		}
	};



};

#endif

