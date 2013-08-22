int external_counter;
extern "C" int public_function();

void function_b()
{
    external_counter += public_function();
}

void function_c()
{
}

void function_d()
{
}
