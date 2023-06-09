// Copyright (c) embedded ocean GmbH
#pragma once

#include "Attributes.hpp"
#include "CustomError.hpp"

#include <xentara/skill/Element.hpp>
#include <xentara/utils/tools/Unique.hpp>
#include <xentara/utils/core/Uuid.hpp>

#include <string_view>
#include <functional>

namespace xentara::plugins::templateDriver
{

using namespace std::literals;

/// @brief A class representing a specific type of I/O component.
/// @todo rename this class to something more descriptive
class TemplateIoComponent final : public skill::Element
{
private:
	/// @brief A structure used to store the class specific attributes within an element's configuration
	struct Config final
	{
		/// @todo Add custom config attributes
	};
	
public:
	/// @brief The class object containing meta-information about this element type
	class Class final : public skill::Element::Class
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

		/// @name Virtual Overrides for skill::Element::Class
		/// @{

		auto name() const -> std::string_view final
		{
			/// @todo change class name
			return "TemplateIoComponent"sv;
		}
	
		auto uuid() const -> utils::core::Uuid final
		{
			/// @todo assign a unique UUID
			return "deadbeef-dead-beef-dead-beefdeadbeef"_uuid;
		}

		/// @}

	private:
	    /// @brief The array handle for the class specific attributes within an element's configuration
		memory::Array::ObjectHandle<Config> _configHandle { config().appendObject<Config>() };

		/// @brief The global object that represents the class
		static Class _instance;
	};

	/// @brief A handle used to access the I/O component
	/// @todo implement a proper handle
	class Handle final : private utils::tools::Unique
	{
	};

	/// @brief Returns a handle to the I/O component
	auto handle() const -> const Handle &
	{
		return _handle;
	}

	/// @name Virtual Overrides for skill::Element
	/// @{

	auto createChildElement(const skill::Element::Class &elementClass, skill::ElementFactory &factory)
		-> std::shared_ptr<skill::Element> final;

	auto forEachAttribute(const model::ForEachAttributeFunction &function) const -> bool final;

	auto makeReadHandle(const model::Attribute &attribute) const noexcept -> std::optional<data::ReadHandle> final;

	auto prepare() -> void final;

	auto cleanup() -> void final;

	/// @}

protected:
	/// @name Virtual Overrides for skill::Element
	/// @{

	auto loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const config::FallbackHandler &fallbackHandler) -> void final;

	/// @}

private:
	/// @brief A handle to the I/O component
	Handle _handle;
};

} // namespace xentara::plugins::templateDriver