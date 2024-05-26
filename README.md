# StealthChanger Knomi Mod
<a href="bin/knomi1.bin">Knomi1 Binary</a>
<a href="bin/knomi2.bin">Knomi2 Binary</a>

### Changes from stock
New Stealthchanger idle animation
<img src="/images/sc.gif" width=250/>

New print screen with live monitoring of the tools temperature.
Swipe from left to right to adjust the nozzle temperature.
<img src="/images/print.png" width=250/>

Added tool page with select, dock and calibration options.
Dock Calibration interface.
Up arrow for positive moves.
Down arrow for negative moves.
Settings button to change axis/increment or test/save position.
<img src="/images/cal1.png" width=250/>

Change axis/increment via scrollbars and confirm changes via button on bottom right
Save calibration (top), test calibration (bottom right)
<img src="/images/cal2.png" width=250/>

Tool changes are recognised and animation plays if docked or selected
<img src="/images/dock.gif" width=250/>

### Changes required to config
Tool ID has changed to Tool Number. Enter only the integer of the tool you want to pair with Knomi
<img src="/images/config.png" width=500/>

Add `variable_active_tool: -1` to `_KNOMI_STATUS` macro
```
[gcode_macro _KNOMI_STATUS]
variable_homing: False
variable_probing: False
variable_qgling: False
variable_heating_nozzle: False
variable_heating_bed: False
variable_active_tool: -1
gcode:
```

Add `SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=active_tool VALUE={tool.tool_number}` to `after_change_gcode`
```
after_change_gcode:
  {% if tool.name %}
    RESPOND TYPE=echo MSG='After changing {tool.name}'
    _TOOLCHANGER_TOOL_AFTER_CHANGE TN={tool.name|replace('tool ', '', 1)}
    SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=active_tool VALUE={tool.tool_number}
  {% else %}
    SET_GCODE_VARIABLE MACRO=_KNOMI_STATUS VARIABLE=active_tool VALUE=-1
  {% endif %}
  ```

