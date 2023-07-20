"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.TSRegister = void 0;
const TSStoryNPC_1 = require("./TSStoryNPC");
const TSStoryTrigger_1 = require("./TSStoryTrigger");
class TSRegister {
    static _TSObjectRegisterMap = new Map([
        ["TSStoryNPC", TSStoryNPC_1.TSStoryNPC],
        ["TSStoryTrigger", TSStoryTrigger_1.TSStoryTrigger],
    ]);
    static GetTSObject(tsName) {
        if (this._TSObjectRegisterMap.has(tsName)) {
            return this._TSObjectRegisterMap.get(tsName);
        }
        return null;
    }
}
exports.TSRegister = TSRegister;
//# sourceMappingURL=TSRegister.js.map