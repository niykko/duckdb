#pragma once
#include "duckdb/common/types/data_chunk.hpp"

namespace duckdb {
struct OrdinalityData {
	static void PrepareOrdinality(DataChunk &chunk, const vector<column_t> &column_ids, idx_t &ord_index) {
		idx_t ordinality = chunk.size();
		if (ordinality > 0) {
			idx_t ordinality_column = column_ids.size() - 1;
			chunk.data[ordinality_column].Sequence(ord_index, 1, ordinality);
		}
	}
	static void PrepareOrdinality(DataChunk &chunk, const vector<column_t> &column_ids, idx_t &ord_index,
	                              bool &ord_reset) {
		const idx_t ordinality = chunk.size();
		if (ordinality > 0) {
			if (ord_reset) {
				ord_index = 1;
				ord_reset = false;
			}
			const idx_t ordinality_column = column_ids.size() - 1;
			chunk.data[ordinality_column].Sequence(ord_index, 1, ordinality);
		}
	}
};
} // namespace duckdb
