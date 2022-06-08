// Copyright (c) embedded ocean GmbH
#pragma once

#include "Attributes.hpp"
#include "CustomError.hpp"

#include <xentara/io/Component.hpp>
#include <xentara/io/ComponentClass.hpp>
#include <xentara/utils/tools/Unique.hpp>
#include <xentara/utils/core/Uuid.hpp>

#include <string_view>
#include <functional>

// TODO: rename namespace
namespace xentara::plugins::templateDriver
{

using namespace std::literals;

// A class representing a specific type of I/O component.
// TODO: rename this class to something more descriptive
class TemplateIoComponent final : public io::Component
{
private:
	// A structure used to store the class specific attributes within an element's configuration
	struct Config final
	{
		// TODO: Add custom config attributes
	};
	
public:
	// The class object containing meta-information about this element type
	class Class final : public io::ComponentClass
	{
	public:
		// Gets the global object
		static auto instance() -> Class&
		{
			return _instance;
		}

	    // Returns the array handle for the class specific attributes within an element's configuration
	    auto configHandle() const -> const auto &
        {
            return _configHandle;
        }

		auto name() const -> std::u16string_view final
		{
			// TODO: change class name
			return u"TemplateIoComponent"sv;
		}
	
		auto uuid() const -> utils::core::Uuid final
		{
			// TODO: assign a unique UUID
			return "bbbbbbbb-bbbb-bbbb-bbbb-bbbbbbbbbbbb"_uuid;
		}

	private:
	    // The array handle for the class specific attributes within an element's configuration
		memory::Array::ObjectHandle<Config> _configHandle { config().appendObject<Config>() };

		// The global object that represents the class
		static Class _instance;
	};

	// A handle used to access the I/O component
	// TODO: implement a proper handle
	class Handle final : private utils::tools::Unique
	{
	};

	// Returns a handle to the I/O component
	auto handle() const -> const Handle &
	{
		return _handle;
	}

	auto createIo(const io::IoClass &ioClass, plugin::SharedFactory<io::Io> &factory) -> std::shared_ptr<io::Io> final;

	auto resolveAttribute(std::u16string_view name) -> const model::Attribute * final;

	auto readHandle(const model::Attribute &attribute) const noexcept -> data::ReadHandle final;

	auto prepare() -> void final;

	auto cleanup() -> void final;

	// TODO: add postPrepare() and preCleanup() functions as necessary

protected:
	auto loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const FallbackConfigHandler &fallbackHandler) -> void final;

private:
	// A handle to the I/O component
	Handle _handle;
};

} // namespace xentara::plugins::templateDriver