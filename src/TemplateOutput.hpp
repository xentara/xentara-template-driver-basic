// Copyright (c) embedded ocean GmbH
#pragma once

#include "ReadState.hpp"
#include "WriteState.hpp"
#include "ReadTask.hpp"
#include "SingleValueQueue.hpp"
#include "WriteTask.hpp"

#include <xentara/io/Io.hpp>
#include <xentara/io/IoClass.hpp>
#include <xentara/plugin/EnableSharedFromThis.hpp>
#include <xentara/process/Task.hpp>

#include <functional>
#include <string_view>

namespace xentara::plugins::templateDriver
{

using namespace std::literals;

class TemplateIoComponent;

/// @brief A class representing a specific type of output.
/// @todo rename this class to something more descriptive
class TemplateOutput final : public io::Io, public plugin::EnableSharedFromThis<TemplateOutput>
{
private:
	/// @brief A structure used to store the class specific attributes within an element's configuration
	struct Config final
	{
		/// @todo Add custom config attributes
	};
	
public:
	/// @brief The class object containing meta-information about this element type
	class Class final : public io::IoClass
	{
	public:
		/// @brief Gets the global object
		static auto instance() -> Class&
		{
			return _instance;
		}

	    /// @brief Returns the array handle for the class specific attributes within an element's configuration
	    auto configHandle() const -> const auto &
        {
            return _configHandle;
        }

		/// @name Virtual Overrides for io::IoClass
		/// @{

		auto name() const -> std::string_view final
		{
			/// @todo change class name
			return "TemplateOutput"sv;
		}
	
		auto uuid() const -> utils::core::Uuid final
		{
			/// @todo assign a unique UUID
			return "dddddddd-dddd-dddd-dddd-dddddddddddd"_uuid;
		}

		/// @}

	private:
	    /// @brief The array handle for the class specific attributes within an element's configuration
		memory::Array::ObjectHandle<Config> _configHandle { config().appendObject<Config>() };

		/// @brief The global object that represents the class
		static Class _instance;
	};

	/// @brief This constructor attaches the output to its I/O component
	TemplateOutput(std::reference_wrapper<TemplateIoComponent> ioComponent) :
		_ioComponent(ioComponent)
	{
	}
	
	/// @name Virtual Overrides for io::Io
	/// @{

	auto dataType() const -> const data::DataType & final;

	auto directions() const -> io::Directions final;

	auto resolveAttribute(std::string_view name) -> const model::Attribute * final;
	
	auto resolveTask(std::string_view name) -> std::shared_ptr<process::Task> final;

	auto resolveEvent(std::string_view name) -> std::shared_ptr<process::Event> final;

	auto readHandle(const model::Attribute &attribute) const noexcept -> data::ReadHandle final;

	auto writeHandle(const model::Attribute &attribute) noexcept -> data::WriteHandle final;

	auto realize() -> void final;

	/// @}

	/// @brief A Xentara attribute containing the current value.
	/// @note This is a member of this class rather than of the attributes namespace, because the access flags
	/// and type may differ from class to class
	static const model::Attribute kValueAttribute;

protected:
	/// @name Virtual Overrides for io::Io
	/// @{

	auto loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const FallbackConfigHandler &fallbackHandler) -> void final;

	/// @}

private:
	// The tasks need access to out private member functions
	friend class ReadTask<TemplateOutput>;
	friend class WriteTask<TemplateOutput>;

	/// @brief This function is called by the "read" task.
	///
	/// This function attempts to read the value if the I/O component is up.
	auto performReadTask(const process::ExecutionContext &context) -> void;
	/// @brief Attempts to read the data from the I/O component and updates the state accordingly.
	auto read(std::chrono::system_clock::time_point timeStamp) -> void;

	/// @brief This function is called by the "write" task.
	///
	/// This function attempts to write the value if the I/O component is up.
	auto performWriteTask(const process::ExecutionContext &context) -> void;
	/// @brief Attempts to write any pending value to the I/O component and updates the state accordingly.
	auto write(std::chrono::system_clock::time_point timeStamp) -> void;	

	/// @brief Invalidates any read data
	auto invalidateData(std::chrono::system_clock::time_point timeStamp) -> void;

	/// @brief Schedules a value to be written.
	/// 
	/// This function is called by the value write handle.
	/// @todo use the correct value type
	auto scheduleOutputValue(double value) noexcept
	{
		_pendingOutputValue.enqueue(value);
	}

	/// @brief The I/O component this output belongs to
	/// @todo give this a more descriptive name, e.g. "_device"
	std::reference_wrapper<TemplateIoComponent> _ioComponent;

	/// @brief The read state
	/// @todo use the correct value type
	ReadState<double> _readState;
	/// @brief The write state
	WriteState _writeState;

	/// @brief The queue for the pending output value
	/// @todo use the correct value type
	SingleValueQueue<double> _pendingOutputValue;

	/// @brief The "read" task
	ReadTask<TemplateOutput> _readTask { *this };
	/// @brief The "write" task
	WriteTask<TemplateOutput> _writeTask { *this };
};

} // namespace xentara::plugins::templateDriver