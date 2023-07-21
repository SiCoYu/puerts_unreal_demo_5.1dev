"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const UE = require("ue");
const puerts_1 = require("puerts");
const TSRegister_1 = require("./Game/TSRegister");
const TSAutoBindActor_1 = require("./Game/TSAutoBindActor");
let xContext = puerts_1.argv.getByName("Context");
function _Mixin(ParentClass, ModulePath, ObjectTakeByNative, Inherit, NoMixinedWarning, SpawnInTS) {
    let tsObj = TSRegister_1.TSRegister.GetTSObject(ModulePath);
    const toJsClass = puerts_1.blueprint.tojs(ParentClass);
    console.log("[CPP2TS] AutoBind ModulePath = " + ModulePath + ", ParentClass = " + ParentClass.GetName());
    let config = {};
    let mixinClass = puerts_1.blueprint.mixin(toJsClass, TSAutoBindActor_1.TSAutoBindActor, config);
    if (mixinClass && SpawnInTS) {
        console.log("[CPP2TS] Spawn Actor From TS = " + mixinClass.name);
        let transform = new UE.Transform(new UE.Rotator(0, 0, 0), new UE.Vector(0, 0, 0), new UE.Vector(1, 1, 1));
        let gameInstance = puerts_1.argv.getByName("GameInstance");
        let tsAutoBindActor = UE.GameplayStatics.BeginDeferredActorSpawnFromClass(gameInstance, mixinClass.StaticClass(), undefined, UE.ESpawnActorCollisionHandlingMethod.Undefined);
        UE.GameplayStatics.FinishSpawningActor(tsAutoBindActor, undefined);
        if (tsAutoBindActor) {
            tsAutoBindActor.SetActorHiddenInGame(false);
            tsAutoBindActor.OnCreate(12345);
        }
    }
    return mixinClass.StaticClass();
}
xContext.CallMixinFromCPP.Bind(_Mixin);
//# sourceMappingURL=AutoMixinTest.js.map