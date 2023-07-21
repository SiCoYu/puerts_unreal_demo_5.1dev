import * as UE from 'ue'
import { argv, blueprint} from 'puerts';
import { TSRegister } from "./Game/TSRegister";
import { TSAutoBindActor } from './Game/TSAutoBindActor';
let xContext = (argv.getByName("Context") as UE.XContext);
function _Mixin(ParentClass: UE.Class, ModulePath: string, ObjectTakeByNative: boolean, Inherit: boolean, NoMixinedWarning: boolean, SpawnInTS : boolean) : UE.Class {
    let tsObj = TSRegister.GetTSObject(ModulePath)
    const toJsClass = blueprint.tojs(ParentClass);
    console.log("[CPP2TS] AutoBind ModulePath = ",ModulePath,", ParentClass = ", ParentClass.GetName());
    let config = {};
    let mixinClass = blueprint.mixin(toJsClass, TSAutoBindActor, config)
    if(mixinClass && SpawnInTS)
    {
        console.log("[CPP2TS] Spawn Actor From TS = ",mixinClass.name);
        let transform = new UE.Transform(new UE.Rotator(0,0,0), new UE.Vector(0,0,0), new UE.Vector(1,1,1));
        let gameInstance = (argv.getByName("GameInstance") as UE.GameInstance);
        let tsAutoBindActor =  UE.GameplayStatics.BeginDeferredActorSpawnFromClass(gameInstance, mixinClass.StaticClass(), undefined, UE.ESpawnActorCollisionHandlingMethod.Undefined) as TSAutoBindActor;
        UE.GameplayStatics.FinishSpawningActor(tsAutoBindActor, undefined);
        if(tsAutoBindActor)
        {
            tsAutoBindActor.SetActorHiddenInGame(false);
            tsAutoBindActor.OnCreate(12345);
        }
    }
    return mixinClass.StaticClass();
}
xContext.ScriptMixInHandle.Bind(_Mixin)