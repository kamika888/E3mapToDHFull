
$ErrorActionPreference = 'Stop'

function Get-Strings($obj) {
    if ($null -eq $obj) { return }

    if ($obj -is [string]) {
        $obj
        return
    }

    if ($obj -is [System.Collections.IDictionary]) {
        foreach ($value in $obj.Values) {
            Get-Strings $value
        }
        return
    }

    if ($obj -is [array]) {
        foreach ($value in $obj) {
            Get-Strings $value
        }
        return
    }

    if ($obj -is [pscustomobject]) {
        foreach ($property in $obj.PSObject.Properties) {
            Get-Strings $property.Value
        }
    }
}

function Deny-Git($reason) {
    @{
        permissionDecision = 'deny'
        permissionDecisionReason = $reason
        hookSpecificOutput = @{
            hookEventName = 'PreToolUse'
            permissionDecision = 'deny'
            permissionDecisionReason = $reason
        }
    } | ConvertTo-Json -Depth 5 -Compress
}

try {
    $raw = [Console]::In.ReadToEnd()
    $event = ConvertFrom-Json -InputObject $raw

    # Support both Copilot and legacy Local event formats.
    $toolName = if ($event.toolName) {
        [string]$event.toolName
    } else {
        [string]$event.tool_name
    }

    $toolArgs = if ($null -ne $event.toolArgs) {
        $event.toolArgs
    } else {
        $event.tool_input
    }

    if (-not $toolName) {
        throw "Missing tool name. Received fields: $($event.PSObject.Properties.Name -join ', ')"
    }

    # Block dedicated Git tools.
    if ($toolName -match '(?i)^git$') {
        Deny-Git 'Git operations are disabled by your security policy.'
        exit 0
    }

    # Examine command arguments for terminal/shell tools.
    $isCommandTool = $toolName -match '(?i)(terminal|powershell|bash|shell|command|exec)'

    if ($isCommandTool) {
        $strings = @(Get-Strings $toolArgs)
        $commandText = $strings -join "`n"

        $gitPattern = '(?i)(?:^|[\s;&|()])(?:&\s*)?(?:"[^"]*[\\/])?(?:''[^'']*[\\/])?git(?:\.exe)?(?=\s|$|["''])'

        if ($commandText -match $gitPattern) {
            Deny-Git 'Git commands are disabled. Use VS Code Source Control manually if Git operations are needed.'
            exit 0
        }
    }

    Write-Output '{}'
}
catch {
    Deny-Git "Git safety hook encountered an error: $($_.Exception.Message)"
    exit 0
}
