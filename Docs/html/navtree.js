var NAVTREE =
[
  [ "Unuk", "index.html", [
    [ "Class List", "annotated.html", [
      [ "AStar", "class_a_star.html", null ],
      [ "Colour", "struct_colour.html", null ],
      [ "Debug", "class_debug.html", null ],
      [ "Entity", "class_entity.html", null ],
      [ "Game", "class_game.html", null ],
      [ "GLXBufferClobberEventSGIX", "struct_g_l_x_buffer_clobber_event_s_g_i_x.html", null ],
      [ "GLXHyperpipeConfigSGIX", "struct_g_l_x_hyperpipe_config_s_g_i_x.html", null ],
      [ "GLXHyperpipeNetworkSGIX", "struct_g_l_x_hyperpipe_network_s_g_i_x.html", null ],
      [ "GLXPipeRect", "struct_g_l_x_pipe_rect.html", null ],
      [ "GLXPipeRectLimits", "struct_g_l_x_pipe_rect_limits.html", null ],
      [ "ImageLoader", "class_image_loader.html", null ],
      [ "input_s", "structinput__s.html", null ],
      [ "keyboard_s", "structkeyboard__s.html", null ],
      [ "mouse_s", "structmouse__s.html", null ],
      [ "Node", "class_node.html", null ],
      [ "Player", "class_player.html", null ],
      [ "Sprite", "class_sprite.html", null ],
      [ "Stack", "struct_stack.html", null ],
      [ "Static", "class_static.html", null ],
      [ "TexCoord", "struct_tex_coord.html", null ],
      [ "Vector2", "struct_vector2.html", null ],
      [ "Win32Window", "class_win32_window.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "AStar", "class_a_star.html", null ],
      [ "Colour", "struct_colour.html", null ],
      [ "Debug", "class_debug.html", null ],
      [ "Game", "class_game.html", null ],
      [ "GLXBufferClobberEventSGIX", "struct_g_l_x_buffer_clobber_event_s_g_i_x.html", null ],
      [ "GLXHyperpipeConfigSGIX", "struct_g_l_x_hyperpipe_config_s_g_i_x.html", null ],
      [ "GLXHyperpipeNetworkSGIX", "struct_g_l_x_hyperpipe_network_s_g_i_x.html", null ],
      [ "GLXPipeRect", "struct_g_l_x_pipe_rect.html", null ],
      [ "GLXPipeRectLimits", "struct_g_l_x_pipe_rect_limits.html", null ],
      [ "ImageLoader", "class_image_loader.html", null ],
      [ "input_s", "structinput__s.html", null ],
      [ "keyboard_s", "structkeyboard__s.html", null ],
      [ "mouse_s", "structmouse__s.html", null ],
      [ "Node", "class_node.html", null ],
      [ "Player", "class_player.html", null ],
      [ "Sprite", "class_sprite.html", null ],
      [ "Stack", "struct_stack.html", null ],
      [ "Static", "class_static.html", [
        [ "Entity", "class_entity.html", null ]
      ] ],
      [ "TexCoord", "struct_tex_coord.html", null ],
      [ "Vector2", "struct_vector2.html", null ],
      [ "Win32Window", "class_win32_window.html", null ]
    ] ],
    [ "Class Members", "functions.html", null ],
    [ "File List", "files.html", [
      [ "src/Libs/glxext.h", "glxext_8h.html", null ],
      [ "src/Libs/wglext.h", "wglext_8h.html", null ],
      [ "src/libUnuk/AStar.cpp", "_a_star_8cpp.html", null ],
      [ "src/libUnuk/AStar.h", "_a_star_8h.html", null ],
      [ "src/libUnuk/Debug.cpp", "_debug_8cpp.html", null ],
      [ "src/libUnuk/Debug.h", "_debug_8h.html", null ],
      [ "src/libUnuk/Entity.cpp", "_entity_8cpp.html", null ],
      [ "src/libUnuk/Entity.h", "_entity_8h.html", null ],
      [ "src/libUnuk/EntityType.h", "_entity_type_8h.html", null ],
      [ "src/libUnuk/Geometry.h", "_geometry_8h.html", null ],
      [ "src/libUnuk/ImageLoader.cpp", "_image_loader_8cpp.html", null ],
      [ "src/libUnuk/ImageLoader.h", "_image_loader_8h.html", null ],
      [ "src/libUnuk/Input.cpp", "_input_8cpp.html", null ],
      [ "src/libUnuk/Input.h", "_input_8h.html", null ],
      [ "src/libUnuk/Node.h", "_node_8h.html", null ],
      [ "src/libUnuk/Sprite.cpp", "_sprite_8cpp.html", null ],
      [ "src/libUnuk/Sprite.h", "_sprite_8h.html", null ],
      [ "src/libUnuk/Static.h", "_static_8h.html", null ],
      [ "src/libUnuk/Win32Window.cpp", "_win32_window_8cpp.html", null ],
      [ "src/libUnuk/Win32Window.h", "_win32_window_8h.html", null ],
      [ "src/Unuk/Game.cpp", "_game_8cpp.html", null ],
      [ "src/Unuk/Game.h", "_game_8h.html", null ],
      [ "src/Unuk/main.cpp", "main_8cpp.html", null ],
      [ "src/Unuk/Player.cpp", "_player_8cpp.html", null ],
      [ "src/Unuk/Player.h", "_player_8h.html", null ]
    ] ],
    [ "File Members", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

