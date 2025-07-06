#include "../../inc/built.h"
#include "../../libft/libft.h"

static int change_data(t_env **env, char *value)
{
    
    return (0);
}

int export_modify(t_data *data, char *s)
{
    t_env *env;
    char *var;
    char *value;
    bool error;

    error = false;
    var = get_var_export(s);
    if (!var)
        return (1);
    value = get_value_export(s, &error);
    if (error)
        return (free(var), 1);
    env = data->env;
    while (env)
    {
        if (!ft_strcmp(env->var, var))
        {
            free(var);
            free(env->value);
            env->value = value;
            return (0);
        }
        env = env->next;
    }
    return (free(var), 0);
}