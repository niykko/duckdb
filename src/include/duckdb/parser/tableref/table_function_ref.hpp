//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parser/tableref/table_function_ref.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/parser/parsed_expression.hpp"
#include "duckdb/parser/tableref.hpp"
#include "duckdb/common/vector.hpp"
#include "duckdb/parser/statement/select_statement.hpp"

namespace duckdb {
//! Represents a Table producing function
class TableFunctionRef : public TableRef {
public:
	static constexpr const TableReferenceType TYPE = TableReferenceType::TABLE_FUNCTION;

public:
	DUCKDB_API TableFunctionRef();

	unique_ptr<ParsedExpression> function;

	// if the function takes a subquery as argument its in here
	unique_ptr<SelectStatement> subquery;

	// External dependencies of this table function
	unique_ptr<ExternalDependency> external_dependency;

	// for WITH ORDINALITY
	bool with_ordinality = false;

public:
	string ToString() const override;

	bool Equals(const TableRef &other_p) const override;

	unique_ptr<TableRef> Copy() override;

	//! Deserializes a blob back into a BaseTableRef
	void Serialize(Serializer &serializer) const override;
	static unique_ptr<TableRef> Deserialize(Deserializer &source);
};
} // namespace duckdb
