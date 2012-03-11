#include <sstream>

#include "Serialiser.h"
#include "Debug.h"

void Serialiser::StepIn(const string& name) {
  if(_currentElement != NULL) {
    // Save the current element as a parent element.
    _parentElements.push_back(_currentElement);
  }

  // Create the new element.
  _currentElement = new TiXmlElement(name.c_str());

  if(_rootElement == NULL) {
    _rootElement = _currentElement;
    _parentElements.push_back(_rootElement);
  }
}

void Serialiser::StepOut(void) {
  if(_parentElements.size() == 0) {
    return;
  }

  TiXmlElement* parentElement = _parentElements.back();
  
  // This happens when stepping out of root.
  if(parentElement == _currentElement) {
    return;
  }

  // Append the current element to the end of the parent element.
  parentElement->LinkEndChild(_currentElement);

  // Set the current element to be the parent element.
  _currentElement = parentElement;

  // Remove the current element from the parent elements list.
  _parentElements.pop_back();
}

bool Serialiser::FirstElement(const string& name) {
  TiXmlElement* oldElement = _currentElement;

  if(!_currentElement) {
    _currentElement = _document.FirstChildElement(name.c_str());
  } else {
    _currentElement = _currentElement->FirstChildElement(name.c_str());
  }

  if(!_currentElement) {
    // Restore the old element if new one was not found.
    _currentElement = oldElement;

    return false;
  }
  
  if(oldElement) {
    // Save the old element as parent.
    _parentElements.push_back(oldElement);
  }

  return true;
}

bool Serialiser::NextElement(const string& name) {
  // Find first element of that name if current one is
  // not named the same.
  if(name != _currentElement->Value()) {
    return FirstElement(name);
  }

  TiXmlElement* oldElement = _currentElement;

  _currentElement = _currentElement->NextSiblingElement(name.c_str());

  if(!_currentElement) {
    // Restore the old element if new one was not found.
    _currentElement = oldElement;
    
    return false;
  }

  return true;
}

void Serialiser::RollBack(void) {
  if(_parentElements.size() > 0) {
    _currentElement = _parentElements.back();
    _parentElements.pop_back();
  }
}

void Serialiser::Load(const string& filename) {
  _document.LoadFile(filename.c_str());
}

void Serialiser::Save(const string& filename) {
  _document.LinkEndChild(_rootElement);
  _document.SaveFile(filename.c_str());
}

void Serialiser::RegisterMember(const string& name, int type, void* data) {
  SerialiserMember member(name, type, data);
  _members.push_back(member);
}

void Serialiser::WriteMembers(void) {
  //Debug::logger->message("WriteMembers()");

  std::stringstream sstream;
  
  for(list<SerialiserMember>::iterator i = _members.begin(); i != _members.end(); ++i) {
    TiXmlText* text = NULL;

    // Convert the data to text.
    if(i->_type == MEMBER_INT) {
      sstream.clear();
      sstream << *((int*)i->_data);
      text = new TiXmlText(sstream.str().c_str());
    } else if(i->_type == MEMBER_FLOAT) {
      sstream.clear();
      sstream << *((float*)i->_data);
      text = new TiXmlText(sstream.str().c_str());
    } else if(i->_type == MEMBER_STRING) {
      text = new TiXmlText((*((string*)i->_data)).c_str());
    } else if(i->_type == MEMBER_BOOL) {
      bool b = *((bool*)i->_data);
      text = new TiXmlText(b ? "true" : "false");
    }

    if(!text) {
      continue;
    }

    TiXmlElement* element = new TiXmlElement(i->_name.c_str());
    element->LinkEndChild(text);

    _currentElement->LinkEndChild(element);
  }

  _members.clear();
}

void Serialiser::ReadMembers(void) {
  for(list<SerialiserMember>::iterator i = _members.begin(); i != _members.end(); ++i) {
    TiXmlElement* element = _currentElement->FirstChildElement(i->_name.c_str());
    
    if(!element) {
      continue;
    }

    // Read the data from the text of the element.
    if(i->_type == MEMBER_INT) {
      *((int*)i->_data) = atoi(element->GetText());
    } else if(i->_type == MEMBER_FLOAT) {
      *((float*)i->_data) = (float)atof(element->GetText());
    } else if(i->_type == MEMBER_STRING) {
      *((string*)i->_data) = string(element->GetText());
    } else if(i->_type == MEMBER_BOOL) {
      if(!strcmp(element->GetText(), "true")) {
        *((bool*)i->_data) = true;
      } else {
        *((bool*)i->_data) = false;
      }
    }
  }

  _members.clear();
}
