static int local_function();

int external_counter;
static int counter;
static int preset_counter = 5;
const int constant = 10;

int public_function()
{
    volatile int i = 3 + constant;
    ++external_counter;
    return local_function() * i;
}

static int local_function()
{
    ++counter;
    ++preset_counter;
    return counter + preset_counter;
}
