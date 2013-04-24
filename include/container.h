#ifndef LIBGOD_INC__CONTAINER_H
#define LIBGOD_INC__CONTAINER_H

namespace libgod
{

	namespace details
	{
		/** Universal sort function for vector */
		template <class T, class Comp>
		void genericSort (typename std::vector<T>& cont, const Comp& comp)
		{
			std::sort(cont.begin(), cont.end(), comp);
		}
		
		/** Universal sort function for list */
		template <class T, class Comp>
		void genericSort (typename std::list<T>& cont, const Comp& comp)
		{
			cont.sort(comp);
		}
	};

	/**
	 * Container class represents a universal storage
	 * for points and sets.
	 * Container supports iterationg through elemements,
	 * accessing by index, adding and removing
	 */
	template <typename T, typename Inner>
	class Container
	{
	protected:
		/** Type itself */
		typedef Container<T, Inner> SelfType;

		/** Whether a container is bare i.e. without data and dimensions */
		bool m_isBare;

		/** Parameter dimension, remembered in container constructing new type instances */
		size_t m_dimParameter;
		/** Criteria dimension, remembered in container constructing new type instances */
		size_t m_dimCriteria;

		/** Data itself */
		Inner m_items;

		/** Derived class name, used for debug purposes */
		const std::string m_classDesc;
		
		/** Metadata associated with data */
		Metadata m_metadata;


		/** Construct a container with the specified dimensions */
		Container (const std::string& classDesc, size_t dimParameter, size_t dimCriteria)
			: m_isBare(false),
				m_dimParameter(dimParameter),
				m_dimCriteria(dimCriteria),
				m_classDesc(classDesc)
			{
				if (dimParameter <= 0 || dimCriteria <= 0)
					throw GodError("dimensions should be posititive");
			}
		
		/** Construct a copy of another container. Container is reshaped. */
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

		/** Construct a bare container with class description */
		explicit Container (const std::string& classDesc)
			: m_isBare(true),
			 	m_dimParameter(1),
				m_dimCriteria(1),
				m_classDesc(classDesc)
			{
			}

		/** Construct a bare container */
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

		/**
		 * Deep equals for container.
		 * Takes container content into account.
		 */
		bool deepEquals (const SelfType& rhs) const
		{
			return
				m_dimParameter == rhs.m_dimParameter &&
				m_dimCriteria == rhs.m_dimCriteria &&
				m_items == rhs.m_items;
		}

		/**
		 * Precondition for all public methods 
		 */
		void preConditionBare() const
		{
			if (m_isBare)
				throw GodError("Trying to get data from bare " + m_classDesc);
		}

	public:
		
		/** Non-constant iterator type */
		typedef typename Inner::iterator iterator;
		/** Constant iterator type */
		typedef typename Inner::const_iterator const_iterator;
	
		/** Assignment operator 
		 * Assignment to non-bare container must follow dimensions
		 * Assignment to bare container must initialize this.
		 */
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
		
		/** Returns count of parameters */
		size_t dimParameter() const
		{
			return m_dimParameter;
		}

		/** Returns count of criteria */
		size_t dimCriteria() const
		{
			return m_dimCriteria;
		}

		/** Return size of the container */
		size_t size() const
		{
			return m_items.size();
		}

		/** Return whether a container is empty */
		bool empty() const
		{
			return m_items.empty();
		}

		/**
		 * Deletes all elements in container but leave dimensions
		 */
		void clear()
		{
			preConditionBare();
			m_items.clear();
		}

		/**
		 * Returns whether a container is bare (non-initialized)
		 */
		bool isBare() const
		{
			return m_isBare;
		}

		/** Return a reference to metadata */
		Metadata& metadata()
		{
			return m_metadata;
		}
		
		/** Return a const reference to metadata */
		const Metadata& metadata() const
		{
			return m_metadata;
		}


		/** Iterator to the beginning of container */
		iterator begin()
		{
			preConditionBare();
			return m_items.begin();
		}

		/** Iterator to the beginning of container */
		const_iterator begin() const
		{
			preConditionBare();
			return m_items.begin();
		}

		/** Iterator to the end of container */
		iterator end()
		{
			preConditionBare();
			return m_items.end();
		}

		/** Iterator to the end of container */
		const_iterator end() const
		{
			preConditionBare();
			return m_items.end();
		}

		/** Return an iterator to the item at index ind */
		iterator atIndex(size_t ind)
		{
			preConditionBare();
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		/** Return an iterator to the item at index ind */
		const_iterator atIndex(size_t ind) const
		{
			preConditionBare();
			if (ind >= size())
				throw GodOutOfRangeError(m_classDesc + " item ", ind, size());
			const_iterator it = begin();
			std::advance(it, ind);
			return it;
		}

		/** Add an empty item with the container dimension and return a reference to it */
		T& add()
		{
			preConditionBare();
			m_items.push_back(T(m_dimParameter, m_dimCriteria));
			return m_items.back();
		}

		/** Add a specified item to the end of container */
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

		/** Remove an item at specified index ind */
		void remove(size_t ind)
		{
			preConditionBare();
			remove(atIndex(ind));
		}

		/** Remove an item at iterator iter */
		void remove(iterator iter)
		{
			preConditionBare();
			if (iter >= end())
				throw GodOutOfRangeError(m_classDesc + " item ", std::distance(begin(), iter), size());
			m_items.erase(iter);
		}

		/** Sort a container with the specified comparison functor */
		template <class Comp>
		void sort(const Comp& comp)
		{
			preConditionBare();
			details::genericSort(m_items, comp);
		}

		/** Access an item at index ind */
		const T& operator[] (size_t ind) const
		{
			return *atIndex(ind);
		}

		/** Access an item at index ind */
		T& operator[] (size_t ind)
		{
			return *atIndex(ind);
		}

		/** Swap items at positions left_ind and right_ind */
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

