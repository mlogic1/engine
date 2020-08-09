#include <string>

namespace Engine
{
    class IIdentifiable
    {
        public:
            virtual std::string GetID() const = 0;
    };
}
