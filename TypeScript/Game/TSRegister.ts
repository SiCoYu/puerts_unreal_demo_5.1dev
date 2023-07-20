import { TSNPC } from "./TSNPC"
import { TSStoryNPC } from "./TSStoryNPC"
import { TSStoryTrigger } from "./TSStoryTrigger"

export interface ITSObjectRegister {}

export class TSRegister implements ITSObjectRegister
{
    private static _TSObjectRegisterMap = new Map<string, any>([
        ["TSStoryNPC", TSStoryNPC],
        ["TSStoryTrigger", TSStoryTrigger],
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

