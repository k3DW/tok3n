#pragma once

namespace k3::tok3n {

enum class ModifierFamily
{
	None,

	apply_into,
	apply,
	complete,
	constant,
	defaulted,
	delimit_keep,
	delimit,
	exactly,
	fn,
	ignore,
	into,
	join,
	multi,

	END
};

} // namespace k3::tok3n
