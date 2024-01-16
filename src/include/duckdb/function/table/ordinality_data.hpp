//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/function/table/ordinality_data.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once
#include "duckdb/common/types/data_chunk.hpp"
namespace duckdb {
struct OrdinalityData {
	bool with_ordinality = false;
	idx_t ordinality_column_id;
	idx_t ord_index = 1;
	bool ord_reset = false;
	bool initialized = false;

	void SetOrdinality(DataChunk &chunk, const vector<column_t> &column_ids) {
		const idx_t ordinality = chunk.size();
		if (ordinality > 0) {
			if (ord_reset) {
				ord_index = 1;
				ord_reset = false;
			}
			D_ASSERT(chunk.data[ordinality_column_id].GetVectorType() == duckdb::VectorType::FLAT_VECTOR);
			D_ASSERT(chunk.data[ordinality_column_id].GetType().id() == duckdb::LogicalType::INTEGER);
			chunk.data[ordinality_column_id].Sequence(ord_index, 1, ordinality);
		}
	}
};
} // namespace duckdb
