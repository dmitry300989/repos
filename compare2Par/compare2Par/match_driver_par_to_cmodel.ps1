
Param
(
	[Parameter(Mandatory=$true, ValueFromPipeline=$true)][System.IO.FileInfo]$DriverPar,
	[Parameter(Mandatory=$true, ValueFromPipeline=$true)][System.IO.FileInfo]$CModelPar
)

$PROCESSED_PAR_NAME='processed'
$NEW_PAR_FILE_NAME='0_EncodeSequence_aligned_with_cmodel.par'
$DriverParDir = $DriverPar.Directory

New-Item -Name $NEW_PAR_FILE_NAME -Path $DriverParDir -Force

$DrParContent = Get-Content $DriverPar -Encoding Ascii
$CMParContent = Get-Content $CModelPar -Encoding Ascii

$CMOnly = @()
$NewDrParContent = @()
for ($i=0; $i -lt $CMParContent.Count; $i++)
{
    $CMParNameRE = $($CMParContent[$i] -replace '=.*','=') + '*'

    $res = $DrParContent -like $CMParNameRE
    if ($res.Count -eq 1)
    {
        $NewDrParContent += $res[0]
        $DrParContent = $DrParContent -replace $res[0],$PROCESSED_PAR_NAME
    }
    else
    {
        $CMOnly += $CMParContent[$i]
    }

}

$NewDrParContent += ''
# $NewDrParContent += 'CModel param not found in driver param:'
$NewDrParContent += 'Driver params not found in CModel params:'
$NewDrParContent += $DrParContent | Where-Object { $_ -ne $PROCESSED_PAR_NAME }

Push-Location $DriverParDir
$NewDrParContent | Set-Content -Path $NEW_PAR_FILE_NAME -Encoding ascii
Pop-Location