// Copyright (c) embedded ocean GmbH
#pragma once

#include <xentara/process/Task.hpp>
#include <xentara/process/ExecutionContext.hpp>

#include <chrono>
#include <functional>

namespace xentara::plugins::templateDriver
{

/// @brief This class providing callbacks for the Xentara scheduler for the "read" task of I/O points
template <typename Target>
class WriteTask final : public process::Task
{
public:
	/// @brief This constuctor attached the task to its target
	WriteTask(std::reference_wrapper<Target> target) : _target(target)
	{
	}

	/// @name Virtual Overrides for process::Task
	/// @{

	auto stages() const -> Stages final
	{
		return Stage::PreOperational | Stage::Operational;
	}

	auto preparePreOperational(const process::ExecutionContext &context) -> Status final;

	auto preOperational(const process::ExecutionContext &context) -> Status final;

	auto operational(const process::ExecutionContext &context) -> void final;
		
	/// @}

private:
	/// @brief A reference to the target element
	std::reference_wrapper<Target> _target;
};

template <typename Target>
auto WriteTask<Target>::preparePreOperational(const process::ExecutionContext &context) -> Status
{
	// We don't actually need to do anything, so just tell the scheduler that it can proceed to the next
	// stage as far as we're concerned
	return Status::Ready;
}

template <typename Target>
auto WriteTask<Target>::preOperational(const process::ExecutionContext &context) -> Status
{
	// We just do the same thing as in the operational stage
	operational(context);

	return Status::Ready;
}

template <typename Target>
auto WriteTask<Target>::operational(const process::ExecutionContext &context) -> void
{
	// read the value
	_target.get().performWriteTask(context);
}

} // namespace xentara::plugins::templateDriver