#include "script.h"

//primitive queue for holding scripts to load
//allows eventHandler and scriptHandler to communicate without circular dependancies
queue<script> primitiveScriptQueue;