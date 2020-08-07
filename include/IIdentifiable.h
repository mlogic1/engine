#include <string>

namespace Engine
{
    class IIdentifiable
    {
        public:
            virtual std::string GetID() = 0;
    };
}