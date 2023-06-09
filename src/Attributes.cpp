// Copyright (c) embedded ocean GmbH
#include "Attributes.hpp"

#include <xentara/data/DataType.hpp>

namespace xentara::plugins::templateDriver::attributes
{

const model::Attribute kError { model::Attribute::kError, model::Attribute::Access::ReadOnly, data::DataType::kErrorCode };

const model::Attribute kWriteError { model::Attribute::kWriteError, model::Attribute::Access::ReadOnly, data::DataType::kErrorCode };

} // namespace xentara::plugins::templateDriver::attributes
