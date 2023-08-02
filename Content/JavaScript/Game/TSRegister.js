"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.TSRegister = void 0;
class TSRegister {
    // private static _instance : TSRegister;
    // private _TSObjectRegisterMap = new Map<string, typeof TSNPC>
    // public static GetInstance() : TSRegister
    // {
    //     if(this._instance)
    //     {
    //         return this._instance;
    //     }
    //     this._instance = new TSRegister();
    //     this._instance.RegisterTSClass();
    //     return this._instance;
    // }
    // RegisterTSClass()
    // {
    //     this._TSObjectRegisterMap.set("TSStoryNPC", TSStoryNPC);
    //     this._TSObjectRegisterMap.set("TSStoryTrigger", TSStoryTrigger);
    //     this._TSObjectRegisterMap.set("TSAutoBindActor", TSAutoBindActor);
    //     this._TSObjectRegisterMap.set("TSManualBindActor", TSManualBindActor);
    // }
    // public GetTSClass(tsName : string) : typeof TSNPC
    // {
    //     if( TSRegister.GetInstance()._TSObjectRegisterMap.has(tsName))
    //     {
    //         return TSRegister.GetInstance()._TSObjectRegisterMap.get(tsName);
    //     }
    //     return null;
    // } 
    static GetTSClassByName(className) {
        let cls = globalThis[className];
        if (cls) {
            console.log("1111111111111111111");
            return cls;
        }
        console.log("22222222222222222222");
        return null;
    }
}
exports.TSRegister = TSRegister;
//# sourceMappingURL=TSRegister.js.map