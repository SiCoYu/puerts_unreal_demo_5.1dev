import * as UE from "ue"
import { TSNPC } from "./TSNPC";

export interface TSManualBindActor extends TSNPC, UE.Game.BP_ManualBindActor.BP_ManualBindActor_C{};
export class TSManualBindActor implements TSManualBindActor {
    OnCreate(ID: number): boolean {
        console.log("[CPP2TS]TSManualBindActor============ID = ", ID)
        return true;
    }
}