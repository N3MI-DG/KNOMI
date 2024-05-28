# StealthChanger Knomi Mod
<a href="https://github.com/N3MI-DG/KNOMI/raw/sc/bin/knomi1.bin">Knomi1 Binary</a><br/>
<a href="https://github.com/N3MI-DG/KNOMI/raw/sc/bin/knomi2.bin">Knomi2 Binary</a>

### Changes from stock
New Stealthchanger idle animation<br/>
<img src="/images/sc.gif" width=250/>

New print screen with live monitoring of the tools temperature.
Swipe from left to right to adjust the nozzle temperature.<br/>
<img src="/images/print.png" width=250/>

Added tool page with select, dock and calibration options.
Dock Calibration interface.
Up arrow for positive moves.
Down arrow for negative moves.
Settings button to change axis/increment or test/save position.<br/>
<img src="/images/cal1.png" width=250/>

Change axis/increment via scrollbars and confirm changes via button on bottom right
Save calibration (top), test calibration (bottom right)<br/>
<img src="/images/cal2.png" width=250/>

Tool changes are recognised and animation plays if docked or selected<br/>
<img src="/images/dock.gif" width=250/>

Knomi devices paired to inactive tool heads display print progress similar to stock while printing. 
The same algorithm as KlipperScreen is now used to determine print progress.

### Changes required to config
Tool ID has changed to Tool Number. Enter only the integer of the tool you want to pair with Knomi<br/>
<img src="/images/config.png" width=500/>

Add `pickup` and `dropoff` variables to `_KNOMI_STATUS` macro
```
[gcode_macro _KNOMI_STATUS]
variable_homing: False
variable_probing: False
variable_qgling: False
variable_heating_nozzle: False
variable_heating_bed: False
variable_dropoff: -1
variable_pickup: -1
```

Add `_KNOMI_STATUS ` changes to `after_change_gcode`, `dropoff_gcode` and `pickup_gcode`.
```
after_change_gcode:
  {% if tool.name %}
    RESPOND TYPE=echo MSG='After changing {tool.name}'
    _TOOLCHANGER_TOOL_AFTER_CHANGE TN={tool.name|replace('tool ', '', 1)}
  {% endif %}
  
  SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=pickup VALUE=-1
  SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=dropoff VALUE=-1

dropoff_gcode:
  {% if tool.name %}
    RESPOND TYPE=echo MSG='Dropping off {tool.name}'
    SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=dropoff VALUE={tool.tool_number}
    _TOOLCHANGER_TOOL_DROPOFF TN={tool.name|replace('tool ', '', 1)}
  {% endif %}

pickup_gcode:
  {% if tool.name %}
    RESPOND TYPE=echo MSG='Picking up {tool.name}'
    SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=dropoff VALUE=-1
    SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=pickup VALUE={tool.tool_number}
    _TOOLCHANGER_TOOL_PICKUP TN={tool.name|replace('tool ', '', 1)}
  {% endif %}
  ```

