// Copyright (c) embedded ocean GmbH
#include "TemplateInput.hpp"

#include "Attributes.hpp"
#include "Tasks.hpp"

#include <xentara/config/Errors.hpp>
#include <xentara/data/DataType.hpp>
#include <xentara/data/ReadHandle.hpp>
#include <xentara/model/Attribute.hpp>
#include <xentara/model/ForEachAttributeFunction.hpp>
#include <xentara/model/ForEachEventFunction.hpp>
#include <xentara/model/ForEachTaskFunction.hpp>
#include <xentara/process/ExecutionContext.hpp>
#include <xentara/utils/json/decoder/Object.hpp>
#include <xentara/utils/json/decoder/Errors.hpp>
#include <xentara/utils/eh/currentErrorCode.hpp>

namespace xentara::plugins::templateDriver
{
	
using namespace std::literals;

const model::Attribute TemplateInput::kValueAttribute { model::Attribute::kValue, model::Attribute::Access::ReadOnly, data::DataType::kFloatingPoint };

auto TemplateInput::load(utils::json::decoder::Object &jsonObject, config::Context &context) -> void
{
	// Go through all the members of the JSON object that represents this object
	for (auto && [name, value] : jsonObject)
    {
		/// @todo load configuration parameters
		if (name == "TODO"sv)
		{
			/// @todo parse the value correctly
			auto todo = value.asNumber<std::uint64_t>();

			/// @todo check that the value is valid
			if (!"TODO")
			{
				/// @todo use an error message that tells the user exactly what is wrong
				utils::json::decoder::throwWithLocation(value, std::runtime_error("TODO is wrong with TODO parameter of template input"));
			}

			/// @todo set the appropriate member variables
		}
		else
		{
            config::throwUnknownParameterError(name);
		}
    }

	/// @todo perform consistency and completeness checks
	if (!"TODO")
	{
		/// @todo use an error message that tells the user exactly what is wrong
		utils::json::decoder::throwWithLocation(jsonObject, std::runtime_error("TODO is wrong with template input"));
	}
}

auto TemplateInput::performReadTask(const process::ExecutionContext &context) -> void
{
	// Read the data
	read(context.scheduledTime());
}

auto TemplateInput::read(std::chrono::system_clock::time_point timeStamp) -> void
{
	try
	{
		/// @todo read the value
		double value = {};

		/// @todo if the read function does not throw errors, but uses return types or internal handle state,
		// throw an std::system_error here on failure, or call _state.update() directly.

		// The read was successful
		_state.update(timeStamp, value);
	}
	catch (const std::exception &)
	{
		// Get the error from the current exception using this special utility function
		const auto error = utils::eh::currentErrorCode();
		// Update the state
		_state.update(timeStamp, utils::eh::unexpected(error));
	}
}

auto TemplateInput::invalidateData(std::chrono::system_clock::time_point timeStamp) -> void
{
	// Set the state to "No Data"
	_state.update(timeStamp, utils::eh::unexpected(CustomError::NoData));
}

auto TemplateInput::dataType() const -> const data::DataType &
{
	return kValueAttribute.dataType();
}

auto TemplateInput::directions() const -> io::Directions
{
	return io::Direction::Input;
}

auto TemplateInput::forEachAttribute(const model::ForEachAttributeFunction &function) const -> bool
{
	return
		// Handle all the attributes we support directly
		function(kValueAttribute) ||

		// Handle the state attributes
		_state.forEachAttribute(function);

	/// @todo handle any additional attributes this class supports, including attributes inherited from the I/O component
}

auto TemplateInput::forEachEvent(const model::ForEachEventFunction &function) -> bool
{
	return
		// Handle the state events
		_state.forEachEvent(function, sharedFromThis());

	/// @todo handle any additional events this class supports, including events inherited from the I/O component
}

auto TemplateInput::forEachTask(const model::ForEachTaskFunction &function) -> bool
{
	// Handle all the tasks we support
	return
		function(tasks::kRead, sharedFromThis(&_readTask));

	/// @todo handle any additional tasks this class supports
}

auto TemplateInput::makeReadHandle(const model::Attribute &attribute) const noexcept -> std::optional<data::ReadHandle>
{
	// Handle the value attribute separately
	if (attribute == kValueAttribute)
	{
		return _state.valueReadHandle();
	}
	
	// Handle the state attributes
	if (auto handle = _state.makeReadHandle(attribute))
	{
		return handle;
	}

	/// @todo handle any additional readable attributes this class supports, including attributes inherited from the I/O component

	return std::nullopt;
}

auto TemplateInput::realize() -> void
{
	// Realize the state object
	_state.realize();
}

} // namespace xentara::plugins::templateDriver