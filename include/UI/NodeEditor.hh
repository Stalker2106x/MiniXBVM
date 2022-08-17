#ifndef NODEEDITOR_HH_
#define NODEEDITOR_HH_

#include <imnodes.h>
#include "Computer/Register.hh"
#include "Computer/Memory.hh"
#include "utils.hh"

#define NODE_ID 100
#define INPUT_ID 1000
#define OUTPUT_ID 2000

class NodeEditor
{
public:
    NodeEditor();
    ~NodeEditor();

    void setVisible(bool show);
    void update();


    void addOutput(const std::string &name);
    void addInput(const std::string &name);

    void drawBus();
    void drawRegister(const std::string &regType, const Register &reg);
    void drawMemory(const std::string &memType, const Memory &mem);
    void checkLinks();
    void drawLinks();
    void draw();
private:
  bool _visible;

  size_t _nodeId;
  size_t _inputId;
  size_t _outputId;

  std::vector<std::pair<size_t, size_t>> _links;
};

#endif /* !NODEEDITOR_HH_ */