#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstring>

Model::Model() : modelListener(0), selectedKettle(0)
{
    memset(kettles, 0, sizeof(kettles));
    kettles[0].id = 0;
    kettles[1].id = 1;
    kettles[2].id = 2;
}

void Model::tick()
{

}
