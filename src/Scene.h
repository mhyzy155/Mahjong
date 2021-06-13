#include <vector>
#include <memory>

#include "Abstractions.h"

class Scene {
   public:
    virtual void draw() = 0;
    virtual bool react() = 0;
    virtual std::unique_ptr<Scene> nextScene() = 0;
    bool isQuit() { return _quit; };
    virtual ~Scene(){};

   protected:
    std::vector<Drawable> drawables;
    std::vector<Drawable> clickables;
    bool _quit;
};