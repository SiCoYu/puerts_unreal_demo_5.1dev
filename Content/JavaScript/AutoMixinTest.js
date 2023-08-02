"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
globalThis["UE"] = require("ue");
globalThis["CPP"] = require("cpp");
const puerts_1 = require("puerts");
const TSRegister_1 = require("./Game/TSRegister");
const TSAutoBindActor_1 = require("./Game/TSAutoBindActor");
console.log("[AutoMixinTest Start]");
let xContext = puerts_1.argv.getByName("Context");
function _Mixin(ParentClass, ModulePath, ObjectTakeByNative, Inherit, NoMixinedWarning, SpawnInTS) {
    let tsObj = TSRegister_1.TSRegister.GetTSClassByName(ModulePath);
    if (tsObj) {
        console.log("[CPP2TS]=" + typeof tsObj);
    }
    const toJsClass = puerts_1.blueprint.tojs(ParentClass);
    console.log("[CPP2TS] AutoBind ModulePath = " + ModulePath + ", ParentClass = " + ParentClass.GetName());
    let config = {};
    let mixinClass = puerts_1.blueprint.mixin(toJsClass, TSAutoBindActor_1.TSAutoBindActor, config);
    return mixinClass.StaticClass();
}
function _UnMixin(TSClassName) {
    console.log("unmixin " + TSClassName);
}
xContext.CallMixinFromCPP.Bind(_Mixin);
xContext.CallUnMixinFromCPP.Bind(_UnMixin);
console.log("[AutoMixinTest End]");
//# sourceMappingURL=AutoMixinTest.js.map