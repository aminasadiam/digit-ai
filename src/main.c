#include "app.h"

int main()
{
    App app;
    init_app(&app);
    run_app(&app);
    destroy_app(&app);
    return 0;
}
