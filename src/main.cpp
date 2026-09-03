#include "raylib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <variant>
#include <map>
#include <unordered_map>
#include <functional>

using namespace std;



class Spritesheet{
    public:
        Spritesheet(Texture2D iTex, Rectangle iFrameDims){
            tex = iTex;
            frame_dims = iFrameDims;
        };
        ~Spritesheet(){
            UnloadTexture(tex);
        };  

        Texture2D GetTexture(){
            return tex;
        };
    private:
        Texture2D tex = {};
        Rectangle frame_dims = {};
};

enum PropertyType{
    INT,
    FLOAT,
    VECTOR2,
    VECTOR3,
    VECTOR4,
    STRING,
    BOOL,
    COLOR
};

using PropertyValue = std::variant<
    int,
    float,
    Vector2,
    Vector3,
    Vector4,
    string,
    bool,
    Color
>;

class Property {
public:
    Property(PropertyValue iValue, PropertyType iType)
        : value(iValue) {
            type = iType;
        }

    PropertyValue value;

    template<typename T>
    T& get() {
        return std::get<T>(value);
    }

    template<typename T>
    const T& get() const {
        return std::get<T>(value);
    }

    PropertyType GetPropertyType(){
        return type;
    }
private:
    
    PropertyType type = {};
};



class Tag{
    public:
    Tag(string iName){
        name = iName;
    };
    void AddProperty(Property prop){
        properties.push_back(prop);
    }
    string name = {};
    vector<Property> properties = {};

    private:
};

class Layer{
    public:
    Layer(string iName){
        name = iName;
    }
    string name = {};
    vector<Rectangle> rects = {};
    
    private:
};

class Frame{
    public:
    Frame(Rectangle rect){
        rect_in_sheet = rect;
    }

    void AddRectangle(string layer_name, Rectangle rect){
        for(auto &l : rect_layers){
            if(l.name==layer_name){
                l.rects.push_back(rect);
            }
        }
    }

    
    void RemoveRectangle(string layer_name, Rectangle rect){
        for(auto &l : rect_layers){
            if(l.name==layer_name){
                l.rects.erase(
                remove_if(
                    l.rects.begin(),
                    l.rects.end(),
                    [&](const Rectangle &r)
                    {
                        return r.x == rect.x &&
                            r.y == rect.y &&
                            r.width == rect.width &&
                            r.height == rect.height;
                    }),
                l.rects.end());

            }
        }
    }
    Rectangle rect_in_sheet;

    vector<Layer> rect_layers = {};
    vector<Tag> tags = {};

    private:
};

class Animation{
    public:
    Animation(string iName){
        name = iName;
    };
    vector<Frame> frames = {};

    private:
        string name = {};
};


enum MenuMode{
    mFILE // to open the file menu
};


enum VisualElementType{
    BUTTON, //For pressing, and displaying text
    CONTAINER, //For containing a collection of buttons
    TEXT, // For displaying just text

};

class VisualElement{
    public:
    Texture2D *tex = {};
    Rectangle img_rect = {};
    Rectangle dims = {};
    VisualElementType type = {};
    float z_val = 0.0f;
    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};
};


class Button : public VisualElement {
    public:
    bool pressed = false;
    MenuMode to_broadcast = {};
    void Broadcast(){

    }
};

class EditorCore{
    public:
    Spritesheet *current_sheet;
    vector<VisualElement*> visual_elements = {};
    MenuMode menu_mode = {};
    void InitAll(){

    };
    void UpdateAll(){

    };
    void DrawAll(){

    };

};


// class


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    // SetWindowFocused();
    SetExitKey(KEY_F10); // uncomment for turning off esc key close window
    InitWindow(800, 800, "Timeline Creator");
    // SetTextureFilter()
    InitAudioDevice();
    SetTargetFPS(60);
    // Image icon;
    // icon = LoadImage("gfx/icon/icon.png");
    // SetWindowIcon(icon);
    // UnloadImage(icon);
    SetWindowPosition(0, 30);
    EditorCore *editor = new EditorCore();

    editor->InitAll();

    
    // Game Loop
    while (WindowShouldClose() == false)
    {
        // Game Logic
        // cout << player.current_stamina << "\n";
        // cout << GetFPS() << "\n";
        editor->UpdateAll();
        BeginDrawing();
        ClearBackground(BLACK);
        editor->DrawAll();
        // Game Drawing

        // uncomment these for helpful debug stuff!
        // cout << GetFPS() << "\n";

        EndDrawing();
    }
    // game.new_scale = 3;

    CloseWindow();
    return 0;
}