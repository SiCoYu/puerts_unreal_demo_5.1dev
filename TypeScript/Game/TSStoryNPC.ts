import {TSNPC} from "./TSNPC";
import * as UE from "ue"

export interface TSStoryNPC extends TSNPC, UE.Game.BP_StoryNPC.BP_StoryNPC_C{};
export class TSStoryNPC implements TSStoryNPC {
    OnCreate(ID: number): boolean {
        console.log("[CPP2TS]============ID = ", ID)
        return true;
    }
}