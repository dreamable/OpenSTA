%module NetworkEdit

%{



using sta::Cell;
using sta::Instance;
using sta::Net;
using sta::Port;
using sta::Pin;
using sta::NetworkEdit;
using sta::cmdEditNetwork;

%}

////////////////////////////////////////////////////////////////
//
// SWIG type definitions.
//
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//
// C++ functions visible as TCL functions.
//
////////////////////////////////////////////////////////////////

%inline %{

Instance *
make_instance_cmd(const char *name,
		  LibertyCell *cell,
		  Instance *parent)
{
  return Sta::sta()->makeInstance(name, cell, parent);
}

void
delete_instance_cmd(Instance *inst)
{
  Sta::sta()->deleteInstance(inst);
}

void
replace_cell_cmd(Instance *inst,
		 LibertyCell *to_cell)
{
  Sta::sta()->replaceCell(inst, to_cell);
}

Net *
make_net_cmd(const char *name,
	     Instance *parent)
{
  Net *net = cmdEditNetwork()->makeNet(name, parent);
  // Sta notification unnecessary.
  return net;
}

void
make_port_pin_cmd(const char *port_name,
                  const char *direction)
{
  Sta::sta()->makePortPin(port_name, direction);
}

void
delete_net_cmd(Net *net)
{
  Sta::sta()->deleteNet(net);
}

void
connect_pin_cmd(Instance *inst,
		Port *port,
		Net *net)
{
  Sta::sta()->connectPin(inst, port, net);
}

void
disconnect_pin_cmd(Pin *pin)
{
  Sta::sta()->disconnectPin(pin);
}

// Notify STA of network change.
void
network_changed()
{
  Sta::sta()->networkChanged();
}

%} // inline
