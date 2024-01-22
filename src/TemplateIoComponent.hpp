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
public:
	/// @brief The class object containing meta-information about this element type
	/// @todo change class name
	/// @todo assign a unique UUID
	/// @todo change display name
	using Class = ConcreteClass<"TemplateIoComponent",
		"deadbeef-dead-beef-dead-beefdeadbeef"_uuid,
		"template driver I/O component">;

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

private:
	/// @name Virtual Overrides for skill::Element
	/// @{

	auto load(utils::json::decoder::Object &jsonObject, config::Context &context) -> void final;

	/// @}

	/// @brief A handle to the I/O component
	Handle _handle;
};

} // namespace xentara::plugins::templateDriver