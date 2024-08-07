// Copyright (c) embedded ocean GmbH
#pragma once

#include "ReadState.hpp"
#include "ReadTask.hpp"

#include <xentara/process/Task.hpp>
#include <xentara/skill/DataPoint.hpp>
#include <xentara/skill/EnableSharedFromThis.hpp>

#include <functional>
#include <string_view>

namespace xentara::plugins::templateDriver
{

using namespace std::literals;

class TemplateIoComponent;

/// @brief A class representing a specific type of input.
/// @todo rename this class to something more descriptive
class TemplateInput final : public skill::DataPoint, public skill::EnableSharedFromThis<TemplateInput>
{
public:
	/// @brief The class object containing meta-information about this element type
	/// @todo change class name
	/// @todo assign a unique UUID
	/// @todo change display name
	using Class = ConcreteClass<"TemplateInput", "deadbeef-dead-beef-dead-beefdeadbeef"_uuid, "template driver input">;

	/// @brief This constructor attaches the input to its I/O component
	TemplateInput(std::reference_wrapper<TemplateIoComponent> ioComponent) :
		_ioComponent(ioComponent)
	{
	}

	/// @name Virtual Overrides for skill::DataPoint
	/// @{
	
	auto dataType() const -> const data::DataType & final;

	auto directions() const -> io::Directions final;

	auto forEachAttribute(const model::ForEachAttributeFunction &function) const -> bool final;
	
	auto forEachEvent(const model::ForEachEventFunction &function) -> bool final;

	auto forEachTask(const model::ForEachTaskFunction &function) -> bool final;

	auto makeReadHandle(const model::Attribute &attribute) const noexcept -> std::optional<data::ReadHandle> final;

	/// @}

	/// @brief A Xentara attribute containing the current value.
	/// @note This is a member of this class rather than of the attributes namespace, because the access flags
	/// and type may differ from class to class
	static const model::Attribute kValueAttribute;

private:
	/// @brief The read task needs access to out private member functions
	friend class ReadTask<TemplateInput>;

	/// @brief This function is called by the "read" task.
	///
	/// This function attempts to read the value if the I/O component is up.
	auto performReadTask(const process::ExecutionContext &context) -> void;
	/// @brief Attempts to read the data from the I/O component and updates the state accordingly.
	auto read(std::chrono::system_clock::time_point timeStamp) -> void;

	/// @brief Invalidates any read data
	auto invalidateData(std::chrono::system_clock::time_point timeStamp) -> void;

	/// @name Virtual Overrides for skill::DataPoint
	/// @{

	auto load(utils::json::decoder::Object &jsonObject, config::Context &context) -> void final;

	auto realize() -> void final;

	/// @}

	/// @brief The I/O component this input belongs to
	/// @todo give this a more descriptive name, e.g. "_device"
	std::reference_wrapper<TemplateIoComponent> _ioComponent;

	/// @brief The state
	/// @todo use the correct value type
	ReadState<double> _state;

	/// @brief The "read" task
	ReadTask<TemplateInput> _readTask { *this };
};

} // namespace xentara::plugins::templateDriver