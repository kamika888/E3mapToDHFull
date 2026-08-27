<#
.SYNOPSIS
  Scan a Darkest Hour event file for localization keys and check their presence in the mod's config localization files.

.DESCRIPTION
  This script finds keys matching patterns like EVT_*, ACTION_NAME_*, ACTIONNAME*, ACTION_* in an event file
  and verifies whether those keys exist in any file under the mod's `config` directory (CSV/TXT).

.PARAMETER EventFile
  Path to the event file to scan. Required.

.PARAMETER ConfigDir
  Optional path to the config directory. If omitted, the script will infer the config folder by
  walking up from the event file's path (assumes event file sits under <modroot>\db\events\).

.PARAMETER ExportCsv
  Optional path to export results as CSV. If provided, writes columns: Key,Found,FileFoundIn

EXAMPLE
  .\Check-EventLocalization.ps1 -EventFile "E:\...\db\events\NewOrderAxis.txt"

#>

[CmdletBinding()]
param(
    [Parameter(Mandatory=$true, Position=0)]
    [string]$EventFile,

    [Parameter(Mandatory=$false)]
    [string]$ConfigDir,

    [Parameter(Mandatory=$false)]
    [string]$ExportCsv
)

function Get-LocalizationKeysFromConfig {
    param(
        [Parameter(Mandatory=$true)][string]$ConfigPath
    )

    $keys = @{}

    if (-not (Test-Path $ConfigPath)) {
        Write-Error "Config path '$ConfigPath' does not exist."
        return $keys
    }

    $patterns = @('*.csv','*.txt')

    foreach ($pat in $patterns) {
        Get-ChildItem -Path $ConfigPath -Filter $pat -File -ErrorAction SilentlyContinue | ForEach-Object {
            $file = $_.FullName
            try {
                $lines = Get-Content -Path $file -ErrorAction Stop
            } catch {
                return
            }

            foreach ($line in $lines) {
                $t = $line.Trim()
                if ([string]::IsNullOrWhiteSpace($t)) { continue }
                if ($t.StartsWith('#')) { continue }
                # split on first comma or semicolon or tab
                $parts = $t -split '[,;\t]', 2
                if ($parts.Count -ge 1) {
                    # Trim surrounding whitespace and any surrounding single or double quotes
                    $key = $parts[0].Trim().Trim('"', "'")
                    if (-not [string]::IsNullOrWhiteSpace($key)) {
                        if (-not $keys.ContainsKey($key)) { $keys[$key] = @() }
                        $keys[$key] += $file
                    }
                }
            }
        }
    }

    return $keys
}

function Find-KeysInEvent {
    param(
        [Parameter(Mandatory=$true)][string]$EventPath
    )

    if (-not (Test-Path $EventPath)) {
        throw "Event file '$EventPath' not found."
    }

    $content = Get-Content -Raw -LiteralPath $EventPath -ErrorAction Stop

    # Regex for keys (word boundaries to avoid partial matches). Case-insensitive to be forgiving.
    $pattern = '\b(EVT_[0-9A-Z_]+|ACTION_NAME_[A-Z_]+|ACTIONNAME[0-9A-Z_]+|ACTION_[0-9A-Z_]+)\b'
    $matches = [regex]::Matches($content, $pattern, [System.Text.RegularExpressions.RegexOptions]::IgnoreCase)

    $found = @()
    foreach ($m in $matches) { $found += $m.Value }

    return ($found | Select-Object -Unique)
}

try {
    $EventFile = (Resolve-Path -LiteralPath $EventFile).Path
} catch {
    Write-Error "Cannot resolve event file path: $_"
    exit 2
}

if (-not $ConfigDir) {
    # Infer config dir by walking up from db\events
    $parent = Split-Path -Path $EventFile -Parent    # ...\db\events
    $dbDir  = Split-Path -Path $parent -Parent       # ...\db
    $root   = Split-Path -Path $dbDir -Parent        # mod root
    $ConfigDir = Join-Path $root 'config'
}

if (-not (Test-Path $ConfigDir)) {
    Write-Warning "Config directory '$ConfigDir' not found. You can pass -ConfigDir to override."
}

Write-Output "Scanning event file: $EventFile"
Write-Output "Using config directory: $ConfigDir"

$eventKeys = Find-KeysInEvent -EventPath $EventFile

if (-not $eventKeys -or $eventKeys.Count -eq 0) {
    Write-Output "No matching localization keys found in the event file."
    exit 0
}

Write-Output "Found keys in event file:`n$($eventKeys -join "`n")`n"

$locKeys = Get-LocalizationKeysFromConfig -ConfigPath $ConfigDir

$report = @()

foreach ($k in $eventKeys) {
    $exists = $false
    $files = $null
    # lookup case-sensitive first, then case-insensitive fallback
    if ($locKeys.ContainsKey($k)) {
        $exists = $true
        $files = $locKeys[$k]
    } else {
        # case-insensitive search
        $match = $locKeys.Keys | Where-Object { $_.ToLower() -eq $k.ToLower() }
        if ($match) {
            $exists = $true
            $files = $locKeys[$match[0]]
        }
    }

    $obj = [PSCustomObject]@{
        Key = $k
        Found = $exists
        FileFoundIn = if ($exists) { ($files -join ';') } else { '' }
    }
    $report += $obj
}

$missing = $report | Where-Object { -not $_.Found }

if ($missing.Count -eq 0) {
    # Print a simple, safe message that avoids parentheses or PowerShell subexpressions
    # which may include characters that confuse CMD when the output is later displayed.
    Write-Output ([string]::Format('All keys were found in the config localization files. {0} keys checked.', $report.Count))
} else {
    Write-Warning "Missing localization keys: $($missing.Count)"
    $missing | ForEach-Object { Write-Output " - $($_.Key)" }
}

if ($ExportCsv) {
    try {
        $report | Export-Csv -Path $ExportCsv -NoTypeInformation -Encoding UTF8
        Write-Output "Exported report to $ExportCsv"
    } catch {
        Write-Warning "Failed to export CSV: $_"
    }
}

# Exit code 0 if none missing, 3 if some missing
if ($missing.Count -gt 0) { exit 3 } else { exit 0 }
