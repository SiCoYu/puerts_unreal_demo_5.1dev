import * as UE from "ue"
import { TSNPC } from "./TSNPC";

export interface TSStoryTrigger extends TSNPC, UE.Game.BP_StoryTrigger.BP_StoryTrigger_C{};
export class TSStoryTrigger implements TSStoryTrigger {
    OnCreate(ID: number): boolean {
        return true;
    }
}