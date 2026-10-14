# Views framework

Views are XML templates rendered by the embedded Lua engine. `${expr}` inserts a
Lua expression, while lines beginning with `%` are Lua code:

```xml
<view>
  % for i,3 do
  <text>${i}</text>
  % end
</view>
```

Templates can read the `method`, `uri`, `action`, `data`, and `model` globals.
The count-form loop shorthand `% for i,3 do` expands to Lua's `for i=1,3 do`.
