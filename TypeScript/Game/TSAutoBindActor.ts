import * as UE from "ue"
import { TSNPC } from "./TSNPC";

export interface TSAutoBindActor extends TSNPC, UE.Game.BP_AutoBindActor.BP_AutoBindActor_C{};
export class TSAutoBindActor implements TSAutoBindActor {
    OnCreate(ID: number): boolean {
        console.log("[CPP2TS]TSAutoBindActor============ID = ", ID)
        return true;
    }
}