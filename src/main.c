#include "app.h"

int main()
{
    App app;
    init_app(&app);
    run_app(&app);
    destroy_app();
    return 0;
}
