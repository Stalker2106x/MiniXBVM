#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "UI/NodeEditor.hh"
#include "App.hh"

NodeEditor::NodeEditor()
{
  ImNodes::CreateContext();
  _visible = true;
}

NodeEditor::~NodeEditor()
{
  ImNodes::DestroyContext();
}

void NodeEditor::setVisible(bool show)
{
    _visible = show;
    if (show) update();
}

void NodeEditor::update()
{
}

void NodeEditor::drawBus()
{
  ImNodes::BeginNode(_nodeId++);

  ImNodes::BeginNodeTitleBar();
  ImGui::TextUnformatted("BUS");
  ImNodes::EndNodeTitleBar();

  ImNodes::BeginInputAttribute(_inputId++);
  ImGui::Text("Inputs");
  ImNodes::EndInputAttribute();

  ImNodes::BeginOutputAttribute(_outputId++);
  ImGui::Text("Outputs");
  ImNodes::EndOutputAttribute();

  ImNodes::EndNode();
}

void NodeEditor::checkLinks()
{
  int start_attr, end_attr;
  if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
  {
    _links.push_back(std::make_pair(start_attr, end_attr));
  }
}

void NodeEditor::drawLinks()
{
  size_t linkId = 1;
  for (auto &it : _links)
  {
    ImNodes::Link(linkId++, it.first, it.second);
  }
}

enum RegisterType {
  ProgramCounter,
  MemoryAdressRegistry,
  InstructionRegister,
  Accumulator,
  BRegister,
  Output,
  StatusRegister
};
enum MemoryType {
  RAM
};

void NodeEditor::addOutput(const std::string &name)
{
  ImNodes::BeginOutputAttribute(_outputId++);
  ImGui::Text(name.c_str());
  ImNodes::EndOutputAttribute();
}

void NodeEditor::addInput(const std::string &name)
{
  ImNodes::BeginInputAttribute(_inputId++);
  ImGui::Text(name.c_str());
  ImNodes::EndInputAttribute();
}

void NodeEditor::drawRegister(const std::string &regType, const Register &reg)
{
    ImNodes::BeginNode(_nodeId++);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(regType.c_str());
    ImNodes::EndNodeTitleBar();

    if (regType == "ProgramCounter")
    {
      addOutput("Output");
    }
    else if (regType == "MemoryAdressRegistry")
    {
      addInput("Input");
    }
    else if (regType == "InstructionRegister")
    {
      addInput("Input");
      addOutput("Output");
    }
    else if (regType == "Accumulator")
    {
      addInput("Input");
      addOutput("Output");
    }
    else if (regType == "InstructionRegister")
    {
      addInput("Input");
      addOutput("Output");
    }
    else if (regType == "BRegister")
    {
      addInput("Input");
      addOutput("Output");
    }
    else if (regType == "Output")
    {
      addInput("Input");
    }
    else if (regType == "StatusRegister")
    {
      addInput("Input");
      addOutput("Input");
    }

    ImNodes::EndNode();
}

void NodeEditor::drawMemory(const std::string &memType, const Memory &reg)
{
    ImNodes::BeginNode(_nodeId++);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(memType.c_str());
    ImNodes::EndNodeTitleBar();

    if (memType == "RAM") {
      addOutput("Input");
    }

    ImNodes::EndNode();
}

void NodeEditor::draw()
{
    if (!_visible) return;
    _nodeId = NODE_ID;
    _inputId = INPUT_ID;
    _outputId = OUTPUT_ID;
    ImGui::Begin("NodeEditor", NULL);

    ImNodes::BeginNodeEditor();

    for (auto& memIt : App::instance->computer->_memories)
    {
      drawMemory(memIt.first, memIt.second);
    }
    for (auto& regIt : App::instance->computer->_registers)
    {
      drawRegister(regIt.first, regIt.second);
    }

    drawBus();
    drawLinks();

    ImNodes::EndNodeEditor();

    checkLinks();

    ImGui::End();
}