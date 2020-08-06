/**
	Scene loader loads scene json data, parses it, and instantiates all scene objects

	@author mlogic1
	@date 04.08.2020.
*/

#include "SceneObject.h"
#include <string>
#include <vector>

namespace Engine
{
    class SceneLoader
    {
        public:
            static std::vector<SceneObject*> LoadScene(const std::string& sceneName);

    };
}
