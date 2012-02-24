#pragma once
#include <string>
#include <list>
#include <tinyxml.h>

#include "Serialisable.h"

using std::string;
using std::list;

enum {
  MEMBER_INT,
  MEMBER_FLOAT,
  MEMBER_BOOL,
  MEMBER_STRING,
};

class SerialiserMember {
public:
  SerialiserMember(const string& name, int type, void* data) : _name(name), _type(type), _data(data) {}

  string  _name;
  int     _type;
  void*   _data;
};

class Serialiser {
public:
  Serialiser(void) : _rootElement(NULL), _currentElement(NULL) {}

  // SERIALISATION:
  // StepIn should be called when a new list of elements/members needs to be created (go further down the tree).
  // StepOut should be called every time the processing of an element is complete (go further up the tree).
  void StepIn(const string& name);
  void StepOut(void);

  // DESERIALISATION:
  // FirstElement is used to find the first child element of the current element.
  // NextElement should be called whenever the next element is requested, if another element
  // was found, it will return true.
  // RollBack will just go back to the parent element.
  bool FirstElement(const string& name);
  bool NextElement(const string& name);
  void RollBack(void);

  // Load should be called before the deserialisation.
  // Save should be called after the serialisation.
  void Load(const string& filename);
  void Save(const string& filename);

  // The members of the element should all be registered with RegisterMember.
  // If serialisation is done, WriteMembers should be called after registration, otherwise,
  // ReadMembers should be called after registration. After ReadMembers/WriteMembers is called,
  // the list of members is clear.
  void RegisterMember(const string& name, int _type, void* data);
  void WriteMembers(void);
  void ReadMembers(void);

private:
  TiXmlDocument _document;
  TiXmlElement* _rootElement;
  TiXmlElement* _currentElement;
  list<TiXmlElement*> _parentElements;
  list<SerialiserMember> _members;
};
