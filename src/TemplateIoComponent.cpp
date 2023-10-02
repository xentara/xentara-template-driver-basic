// Copyright (c) embedded ocean GmbH
#include "TemplateIoComponent.hpp"

#include "Attributes.hpp"
#include "TemplateInput.hpp"
#include "TemplateOutput.hpp"

#include <xentara/config/FallbackHandler.hpp>
#include <xentara/data/ReadHandle.hpp>
#include <xentara/model/Attribute.hpp>
#include <xentara/model/ForEachAttributeFunction.hpp>
#include <xentara/skill/ElementFactory.hpp>
#include <xentara/utils/json/decoder/Object.hpp>
#include <xentara/utils/json/decoder/Errors.hpp>

#include <string_view>

namespace xentara::plugins::templateDriver
{

using namespace std::literals;

auto TemplateIoComponent::load(utils::json::decoder::Object &jsonObject,
	config::Resolver &resolver,
	const config::FallbackHandler &fallbackHandler) -> void
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
				utils::json::decoder::throwWithLocation(value, std::runtime_error("TODO is wrong with TODO parameter of template I/O component"));
			}

			/// @todo set the appropriate member variables
		}
		else
		{
			// Pass any unknown parameters on to the fallback handler, which will load the built-in parameters ("id", "uuid", and "children"),
			// and throw an exception if the key is unknown
            fallbackHandler(name, value);
		}
    }

	/// @todo perform consistency and completeness checks
	if (!"TODO")
	{
		/// @todo use an error message that tells the user exactly what is wrong
		utils::json::decoder::throwWithLocation(jsonObject, std::runtime_error("TODO is wrong with template I/O component"));
	}
}

auto TemplateIoComponent::createChildElement(const skill::Element::Class &elementClass, skill::ElementFactory &factory)
	-> std::shared_ptr<skill::Element>
{
	if (&elementClass == &TemplateInput::Class::instance())
	{
		return factory.makeShared<TemplateInput>(*this);
	}
	else if (&elementClass == &TemplateOutput::Class::instance())
	{
		return factory.makeShared<TemplateOutput>(*this);
	}

	/// @todo add any other supported child element types

	return nullptr;
}

auto TemplateIoComponent::forEachAttribute(const model::ForEachAttributeFunction &function) const -> bool
{
	/// @todo call the function with any attributes this class supports

	return false;
}

auto TemplateIoComponent::makeReadHandle(const model::Attribute &attribute) const noexcept -> std::optional<data::ReadHandle>
{
	/// @todo create read handles for any readable attributes this class supports

	// Nothing found
	return std::nullopt;
}

auto TemplateIoComponent::prepare() -> void
{
	/// @todo open the handle for the I/O device
}

auto TemplateIoComponent::cleanup() -> void
{
	/// @todo close the handle to the I/O device
}

} // namespace xentara::plugins::templateDriver