#!/usr/bin/env node

/** 
 * gitComment(weave trace commands into C functions)
 **/

const glstools = require('glstools');
const gprocs = glstools.procs;
const gstrings = glstools.strings;
const gfiles = glstools.files;
const fs = require("fs");
const path = require("path");

let DEBUG = true;
function debug() {
    if (DEBUG) console.log(...arguments);
}
function die() {
    console.error(...arguments);
    process.exit(1);
}

function trace(dir, fn_name) {
    if (fn_name.startsWith("*")) fn_name = fn_name.substring(1);
    return `TRACE("${dir} ${fn_name}");`;
}

function assign_trace(varname) {
    return `TRACE("${varname}=%p", ${varname});`;
}

function weave(lines) {
    let fn_regex = /(.*?)([a-zA-Z0-9_]+) +([*a-zA-Z0-9_]+) *(\(.*\))/
    let return_regex = /return .*;/
    let assign_regex = /([.a-zA-Z0-9_$>-]+) [+-]{0,1}= (.*);/
    let indent = 0;
    let results = [];
    let prefix, return_type, fn_name, parms, return_line;
    for (let line of lines) {
        let fn_matches = line.match(fn_regex);
        let return_matches = line.match(return_regex);
        if (fn_matches) {
            prefix = fn_matches[1];
            return_type = fn_matches[2];
            fn_name = fn_matches[3];
            parms = fn_matches[4];
        }
        if (return_matches) {
            if (line.trim().startsWith("return") && indent === 1) {
                // prevents end of line return statement
                // only captures end of function return statement
                return_line = line;
            }
        }
        if (line.includes("{")) {
            // start of body
            indent++;
            results.push(line);
            if (indent === 1) {
                // start of function
                if (fn_name) results.push(trace(">", fn_name));
            }
        } else if (line.includes("}")) {
            // end of body
            indent--;
            if (indent === 0) {
                // end of function
                if (fn_name) results.push(trace("<", fn_name));
                return_line = null;
                if (return_line) results.push(return_line);
            }
            results.push(line);
        } else {
            if (!return_line) {
                // defer return line until end of function
                results.push(line);
                line = line.replaceAll(/".*?"/g, "");
                let assign_matches = line.match(assign_regex);
                if (assign_matches) {
                    let var_name = assign_matches[1];
                    if (!var_name.includes(".")) results.push(assign_trace(assign_matches[1]));
                }        
            }
        }
    }
    return results;
}


async function main$(_opts) {
    let opts = _opts || gprocs.args("--bucket=devcybiko.s3,--outdir=metadata,--prefix=Music/Music,--file=", "infile*,outfile*");
    let lines = gfiles.readList(opts.infile);
    let results = weave(lines);
    gfiles.writeList(opts.outfile, results);

}

module.exports = { main$ }

if (module.id === ".") {
    return main$();
}
