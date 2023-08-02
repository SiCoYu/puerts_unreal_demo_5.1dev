(<any>globalThis)["UE"] = require("ue");
(<any>globalThis)["CPP"] = require("cpp");

import * as UE from 'ue'
import { argv, blueprint} from 'puerts';
import { TSRegister } from "./Game/TSRegister";
import { TSAutoBindActor } from './Game/TSAutoBindActor';

console.log("[AutoMixinTest Start]");
let xContext = (argv.getByName("Context") as UE.XContext);
function _Mixin(ParentClass: UE.Class, ModulePath: string, ObjectTakeByNative: boolean, Inherit: boolean, NoMixinedWarning: boolean, SpawnInTS : boolean) : UE.Class {
    let tsObj = TSRegister.GetTSClassByName(ModulePath)
    if(tsObj)
    {
        console.log("[CPP2TS]=" + typeof tsObj);
    }
    const toJsClass = blueprint.tojs(ParentClass);
    console.log("[CPP2TS] AutoBind ModulePath = " + ModulePath + ", ParentClass = " + ParentClass.GetName());
    let config = {};
    let mixinClass = blueprint.mixin(toJsClass, TSAutoBindActor, config)
    return mixinClass.StaticClass();
}

function _UnMixin(TSClassName : string) {
    console.log("unmixin "+TSClassName);
}
xContext.CallMixinFromCPP.Bind(_Mixin)
xContext.CallUnMixinFromCPP.Bind(_UnMixin);
console.log("[AutoMixinTest End]");

let gameInstance = (argv.getByName("GameInstance") as UE.GameInstance);
blueprint.load(UE.Game.BP_AutoBindActor.BP_AutoBindActor_C);
const BP_AutoBindActor_C = UE.Game.BP_AutoBindActor.BP_AutoBindActor_C;//别名
let tsAutoBindActor =  UE.GameplayStatics.BeginDeferredActorSpawnFromClass(gameInstance, BP_AutoBindActor_C.StaticClass(), undefined, UE.ESpawnActorCollisionHandlingMethod.Undefined) as TSAutoBindActor;
UE.GameplayStatics.FinishSpawningActor(tsAutoBindActor, undefined);
if(tsAutoBindActor)
{
    tsAutoBindActor.SetActorHiddenInGame(false);
    tsAutoBindActor.OnCreate(12345);
}
//如果确定后续不需要使用TestBlueprint_C了，应该unload节省内存
blueprint.unload(BP_AutoBindActor_C);