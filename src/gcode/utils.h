#ifndef UTILS_H
#define UTILS_H

#define LC_GCODE_COMMAND_ATTR_ACCESSOR_GENERATOR(COMMAND, COMMAND_TYPE, ATTR) \
            bool inline lc_gcode_##COMMAND##_command_get_attr_##ATTR(const lc_gcode_obj_t *command, float *value) \
            {                                                                                     \
                COMMAND_TYPE *g_command = (COMMAND_TYPE *) command;               \
                LC_ASSERT(command, "gcode obj can't be a NULL pointer!");                         \
                *value = g_command->ATTR.value;                                                   \
                return g_command->ATTR.existed;                                                   \
            };

#endif