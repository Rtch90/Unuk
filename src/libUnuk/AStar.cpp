#include <stdlib.h>
#include "AStar.h"
#include "Node.h"

AStar::AStar(void) {
  m_open    	  = NULL;
  m_stack  	  = NULL;
  m_best    	  = NULL;
  
  udCost    	  = NULL;
  udValid   	  = NULL;
  udNotifyChild   = NULL;  
  udNotifyList	  = NULL;
}

AStar::~AStar(void) {
  ClearNodes();
}

bool AStar::GeneratePath(int startx, int starty, int destx, int desty) {
  // Grab the next node from the f position.
  InitStep(startx, starty, destx, desty);

  int retval = 0;
  while(retval == 0) {
    // Go find the next node.
    retval = Step();
  }
  
  if(retval == 0 || !m_best) {
    // Set m_best to NULL so we can go and check for the next best node.
    m_best = NULL;
    return false;
  }
  return true;
}

int AStar::Step(void) {
  // If we don't get the most efficent route, then go back
  // and check some more nodes plox!
  if(!(m_best == GetBest())) { return -1; }
  // Ok, we found the best route.
  if(m_best->id  == m_ID)    { return 1; }
  
  // Please set the best route as a child node.
  CreateChildren(m_best);
 
  return 0;
}

int AStar::InitStep(int startx, int starty, int destx, int desty) {
  // Prepare for the next pass by clearing our previous nodes.
  ClearNodes();
  
  // Initialize our variables.
  m_startx = startx;
  m_starty = starty;
  m_destx  = destx;
  m_desty  = desty;
  m_ID = Coord2Id(destx, desty);
 
  // Set the node for our start location.
  Node *temp = new Node(startx, starty);
  temp->g = 0;
  temp->h = abs(destx - startx) + abs(desty - starty);
  temp->f = temp->g + temp->h;
  temp->id = Coord2Id(startx, starty);
  m_open = temp;

  return 0;
}

void AStar::AddToOpen(Node *addnode) {
  Node *node = m_open;
  Node *prev = NULL;
  
  if(!m_open) {
    // Add a a new node to the open list.
    m_open = addnode;
  
    m_open->next = NULL;

    // Start a new open list with our new node.
    //Func(udNotifyList, NULL, addnode, NL_STARTOPEN, NCData);
 
    return;
  }
  
  while(node) {
    // If our addnode's f is greater than the currently open node
    // then add the open node to the to previous to make room for
    // add node to be on the open list.
    if(addnode->f > node->f) {
      prev = node;
      // Now we have our new node go to next.
      node = node->next;
    } else {
      // go to the next node, and set it on our open list to check it's
      // f value.
      if(prev) {
        prev->next = addnode;
        addnode->next = node;
        Func(udNotifyList, prev, addnode, NL_ADDOPEN, NCData);
      } else {
        // We will only ever run through this once per instance. We have no nodes currently
	// so we set an open list with this node.
        Node *temp = m_open;
      
        m_open = addnode;
        m_open->next = temp;
        //Func(udNotifyList, temp, addnode, NL_STARTOPEN, NCData);
      } 
      return;
    }
  }
  // Get the next node and add it to the open list.
  prev->next = addnode;
  //Func(udNotifyList, prev, addnode, NL_ADDOPEN, NCData);              
}

void AStar::ClearNodes(void) {
  Node *temp  = NULL;
  Node *temp2 = NULL;
  
  if(m_open) {
    while(m_open) {
      temp = m_open->next;
      delete m_open;
      m_open = temp;
    }
  }
  if(m_closed) {
    while(m_closed) {
      temp = m_closed->next;
      delete m_closed;
      m_closed = temp;
    }
  }
}

void AStar::CreateChildren(Node *node) {
  Node temp;
  int x = node->x;
  int y = node->y;
 
  // Loop through the grid and add the children to the list.
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      temp.x = x+i;
      temp.y = y+j;
      if((i == 0) && (j == 0) || !Func(udValid, node, &temp, NC_INITIALADD, CBData)) continue;
	
      LinkChild(node, &temp);
    }
  }	
}

void AStar::LinkChild(Node *node, Node *temp) {
  // Initialize variables for our temp node.
  int x = temp->x;
  int y = temp->y;
  int g = temp->g + Func(udCost, node, temp, 0, CBData);
  // Grabbing a unique ID before adding the node to the open list.
  int id = Coord2Id(x, y);
  
  Node *check = NULL;
  
  if(check = CheckList(m_open, id)) {
    node->children[node->numChildren++] = check;
    
    // We have found an awesome route, update the node and variables.
    if(g < check->g) {
      check->parent = node;
      check->g 	    = g;
      check->f	    = g+check->h;
      //Func(udNotifyChild, node, check, NC_OPENADD_UP, NCData);
    } else {
      //Func(udNotifyChild, node, check, 2, NCData);
    }
  } else if(check = CheckList(m_closed, id)) {
    node->children[node->numChildren++] = check;
      
    if(g < check->g) {
    check->parent = node;
    check->g      = g;
    check->f      = g+check->h;
    //Func(udNotifyChild, node, check, 3, NCData);

    // Update the parents.
    UpdateParents(check);
    } else {
      //Func(udNotifyChild, node, check, 4, NCData);
    }
  } else {
    Node *newnode = new Node(x, y);
    newnode->parent = node;
    newnode->g  = g;
    newnode->h  = abs(x - m_destx) + abs(y - m_desty);
    newnode->f  = newnode->g + newnode->h;
    newnode->id = Coord2Id(x, y);
        
    AddToOpen(newnode);
    node->children[node->numChildren++] = newnode;
    
    //Func(udNotifyChild, node, newnode, 5, NCData);
  }
}  


void AStar::UpdateParent(Node *node) {
  int g = node->g;
  int c = node->numChildren;
  
  Node *child = NULL;
  for(int i = 0; i < c; i++) {
    child = node->children[i];
    if(g + 1 < child->g) {
      child->g = g + 1;
      child->f = child->g + child->h;
      child->parent = node;
      Push(child);
    } 
  }
  Node *parent;
  
  while(m_stack) {
    parent = Pop();
    c = parent->numC22hildren;
    for(int i = 0; i < c; i++) {
      child = parent->children[i];

      if(parent->g + 1 < child->g) {
        child->g = parent->g + Func(udCost, parent, child, NC_INITIALADD, CBData);
        child->f = child->g + child->h;
        child->parent = parent;
        Push(child);
      }
    }
  }
}

void AStar::Push(Node *node) {
  if(!m_stack) {
     m_stack = new Stack;
     m_stack->data = node;
     m_stack->next = NULL;
  } else {
    Stack *temp = new Stack;
    temp->data  = node;
    temp->next  = m_stack;
    m_stack = temp;
  }    
}

Node AStar::*Pop(void) {
  Node *data  = m_stack->data;
  Stack *temp = m_stack;

  m_stack = temp->next;
  delete temp;

  return data;
}

Node AStar::*CheckList(Node *node, int id) {
  while(node) {
    if(node->id == id)  return node; 
    
    node = node->next;
  }
  return NULL;
}

// Get the best node in the open list to enable us to find
// the best route to take.
Node AStar::*GetBest(void) {
  if(!m_open) { return NULL; }
  
  Node *temp  = m_open;
  Node *temp2 = m_closed;
  m_open = temp->next;

  //Func(udNotifyList, NULL, temp, NL_DELETEOPEN, NCData);                           
  m_closed = temp;
  m_closed->next = temp2;
  //Func(udNotifyList, NULL, m_closed, NL_ADDCLOSED, NCData);

  return temp;
}
