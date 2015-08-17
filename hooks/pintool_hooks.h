#ifndef PINTOOL_HOOKS_H_
#define PINTOOL_HOOKS_H_

#define ATTR_HOOK_FUNC __attribute__((externally_visible,noinline))

void pintool_roi_begin() ATTR_HOOK_FUNC;
void pintool_roi_end() ATTR_HOOK_FUNC;

#endif // PINTOOL_HOOKS_H_
