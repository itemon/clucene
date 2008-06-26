/*------------------------------------------------------------------------------
* Copyright (C) 2003-2006 Ben van Klinken and the CLucene Team
* 
* Distributable under the terms of either the Apache License (Version 2.0) or 
* the GNU Lesser General Public License, as specified in the COPYING file.
------------------------------------------------------------------------------*/
#ifndef _lucene_search_Query_h
#define _lucene_search_Query_h


//#include "CLucene/index/IndexReader.h"
CL_CLASS_DEF(index,IndexReader)
//#include "Filter.h"
//#include "Sort.h"
//#include "CLucene/util/VoidList.h"
//#include "Explanation.h"
//#include "Similarity.h"

CL_NS_DEF(search)
    class Weight;
    class Similarity;
    class Searcher;
    
	/** The abstract base class for queries.
    <p>Instantiable subclasses are:
    <ul>
    <li> {@link TermQuery}
    <li> {@link MultiTermQuery}
    <li> {@link BooleanQuery}
    <li> {@link WildcardQuery}
    <li> {@link PhraseQuery}
    <li> {@link PrefixQuery}
    <li> {@link PhrasePrefixQuery}
    <li> {@link FuzzyQuery}
    <li> {@link RangeQuery}
    <li> {@link spans.SpanQuery}
    </ul>
    <p>A parser for queries is contained in:
    <ul>
    <li>{@link queryParser.QueryParser QueryParser}
    </ul>
	*/
	class CLUCENE_EXPORT Query :LUCENE_BASE { 
	private:
		// query boost factor
		float_t boost;
	protected:
		Query(const Query& clone);
	public:
		Query();
		virtual ~Query();

		/** Sets the boost for this query clause to <code>b</code>.  Documents
		* matching this clause will (in addition to the normal weightings) have
		* their score multiplied by <code>b</code>.
		*/
		void setBoost(float_t b);

		/** Gets the boost for this clause.  Documents matching
		* this clause will (in addition to the normal weightings) have their score
		* multiplied by <code>b</code>.   The boost is 1.0 by default.
		*/
		float_t getBoost() const;

        /** Expert: Constructs an initializes a Weight for a top-level query. */
        Weight* weight(Searcher* searcher);

        /** Expert: called to re-write queries into primitive queries. */
        virtual Query* rewrite(CL_NS(index)::IndexReader* reader);
        
        /** Expert: called when re-writing queries under MultiSearcher.
         *
         * <p>Only implemented by derived queries, with no
         * {@link #_createWeight(Searcher)} implementatation.
         */
         virtual Query* combine(Query** queries);

        /** Expert: merges the clauses of a set of BooleanQuery's into a single
         * BooleanQuery.
         *
         *<p>A utility for use by {@link #combine(Query[])} implementations.
	     */
        static Query* mergeBooleanQueries(Query** queries);

        /** Expert: Returns the Similarity implementation to be used for this query.
        * Subclasses may override this method to specify their own Similarity
        * implementation, perhaps one that delegates through that of the Searcher.
        * By default the Searcher's Similarity implementation is returned.*/
        Similarity* getSimilarity(Searcher* searcher);
        
        /** Returns a clone of this query. */
        virtual Query* clone() const = 0;
        virtual const TCHAR* getQueryName() const = 0;
        bool instanceOf(const TCHAR* other) const;
        
		/** Prints a query to a string, with <code>field</code> assumed to be the 
		* default field and omitted.
		* <p>The representation used is one that is supposed to be readable
		* by {@link org.apache.lucene.queryParser.QueryParser QueryParser}. However,
		* there are the following limitations:
		* <ul>
		*  <li>If the query was created by the parser, the printed
		*  representation may not be exactly what was parsed. For example,
		*  characters that need to be escaped will be represented without
		*  the required backslash.</li>
		* <li>Some of the more complicated queries (e.g. span queries)
		*  don't have a representation that can be parsed by QueryParser.</li>
		* </ul>
		*/
        virtual TCHAR* toString(const TCHAR* field) const = 0;
        
        virtual bool equals(Query* other) const = 0;
        virtual size_t hashCode() const = 0;
        
        /** Prints a query to a string. */
        TCHAR* toString() const;

		
		/** Expert: Constructs an appropriate Weight implementation for this query.
		*
		* <p>Only implemented by primitive queries, which re-write to themselves.
		* <i>This is an Internal function</i>
		*/
		virtual Weight* _createWeight(Searcher* searcher);
		
	};
    
CL_NS_END
#endif