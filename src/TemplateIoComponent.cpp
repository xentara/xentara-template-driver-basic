// Copyright (c) embedded ocean GmbH
#include "TemplateIoComponent.hpp"

#include "Attributes.hpp"
#include "TemplateInput.hpp"
#include "TemplateOutput.hpp"

#include <xentara/data/ReadHandle.hpp>
#include <xentara/model/Attribute.hpp>
#include <xentara/plugin/SharedFactory.hpp>
#include <xentara/utils/json/decoder/Object.hpp>
#include <xentara/utils/json/decoder/Errors.hpp>

#include <string_view>

namespace xentara::plugins::templateDriver
{

using namespace std::literals;

TemplateIoComponent::Class TemplateIoComponent::Class::_instance;

auto TemplateIoComponent::loadConfig(const ConfigIntializer &initializer,
		utils::json::decoder::Object &jsonObject,
		config::Resolver &resolver,
		const FallbackConfigHandler &fallbackHandler) -> void
{
	// Get a reference that allows us to modify our own config attributes
    auto &&configAttributes = initializer[Class::instance().configHandle()];

	// Go through all the members of the JSON object that represents this object
	for (auto && [name, value] : jsonObject)
    {
		// TODO: load configuration parameters
		if (name == u8"TODO"sv)
		{
			// TODO: parse the value correctly
			auto todo = value.asNumber<std::uint64_t>();

			// TODO: check that the value is valid
			if (!"TODO")
			{
				// TODO: use an error message that tells the user exactly what is wrong
				utils::json::decoder::throwWithLocation(value, std::runtime_error("TODO is wrong with TODO parameter of template I/O component"));
			}

			// TODO: set the appropriate member variables, and update configAttributes accordingly (if necessary) 
		}
		else
		{
			// Pass any unknown parameters on to the fallback handler, which will load the built-in parameters ("id", "uuid", and "children"),
			// and throw an exception if the key is unknown
            fallbackHandler(name, value);
		}
    }

	// TODO: perform consistency and completeness checks
	if (!"TODO")
	{
		// TODO: use an error message that tells the user exactly what is wrong
		utils::json::decoder::throwWithLocation(jsonObject, std::runtime_error("TODO is wrong with template I/O component"));
	}
}

auto TemplateIoComponent::createIo(const io::IoClass &ioClass, plugin::SharedFactory<io::Io> &factory)
	-> std::shared_ptr<io::Io>
{
	if (&ioClass == &TemplateInput::Class::instance())
	{
		return factory.makeShared<TemplateInput>(*this);
	}
	else if (&ioClass == &TemplateOutput::Class::instance())
	{
		return factory.makeShared<TemplateOutput>(*this);
	}

	// TODO: add any other supported I/O point types

	return nullptr;
}

auto TemplateIoComponent::resolveAttribute(std::u16string_view name) -> const model::Attribute *
{
	// TODO: resolve any attributes this class supports using model::Attribute::resolve
	return nullptr;
}

auto TemplateIoComponent::readHandle(const model::Attribute &attribute) const noexcept -> data::ReadHandle
{
	// TODO create read handles for any attributes this class supports

	// Nothing found
	return data::ReadHandle::Error::Unknown;
}

auto TemplateIoComponent::prepare() -> void
{
	// TODO: open the handle for the I/O device
}

auto TemplateIoComponent::cleanup() -> void
{
	// TODO: close the handle to the I/O device
}

} // namespace xentara::plugins::templateDriver