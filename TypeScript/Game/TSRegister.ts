import { TSNPC } from "./TSNPC"
import { TSStoryNPC } from "./TSStoryNPC"
import { TSStoryTrigger } from "./TSStoryTrigger"
import { TSAutoBindActor } from "./TSAutoBindActor"
import { TSManualBindActor } from "./TSManualBindActor"

export interface ITSObjectRegister {}

export class TSRegister implements ITSObjectRegister
{
    private static _TSObjectRegisterMap = new Map<string, any>([
        ["TSStoryNPC", TSStoryNPC],
        ["TSStoryTrigger", TSStoryTrigger],
        ["TSAutoBindActor", TSAutoBindActor],
        ["TSManualBindActor", TSManualBindActor],
    ])

    static GetTSObject(tsName : string) : TSNPC
    {
        if(this._TSObjectRegisterMap.has(tsName))
        {
            return this._TSObjectRegisterMap.get(tsName);
        }
        return null;
    }    
}

